#include "Server.h"
#include "Helper.h"
#include "DataCenter.h"

Server::Server(int __port) {
    if (__port > 1024) {
        initialize(__port);
        cout << "Server will be bound to port: " << __port << endl;
    } else {
        initialize(DEFAULT_PORT);
        cout << "Invalid Port. Server will be bound to default port: " << DEFAULT_PORT << endl;
    }
}

Server::Server() {
    initialize(DEFAULT_PORT);
    cout << "Server will be bound to default port: " << port << endl;
}

void Server::Initialize(int __port) {
    port = __port;
    FD_ZERO(&fd_accept);
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    cout << "Server initialized" << endl;

    o_DataCenter.InitializeData("data.csv"); // todo x
}

bool Server::binding() {
    struct sockaddr_in ServerAddr;
    int response;
    int optValue = 1;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
    	cout << "ERROR opening socket" << endl;
        return false;
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(int)) == -1) {
    	cout << "ERROR setting socket options" << endl;
        return false;
    }

    bzero((char *) &ServerAddr, sizeof(ServerAddr));

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = INADDR_ANY;
    ServerAddr.sin_port = htons(port);

    if (bind(socket_fd, (struct sockaddr *) &ServerAddr, sizeof(ServerAddr)) < 0)
        return false;

    cout << "Server is listening to " << port << endl;
    listen(socket_fd, 5);

    fcntl(socket_fd, F_SETFL, fcntl(socket_fd, F_GETFL) | O_NONBLOCK);

    max_fd = socket_fd;
    return true;
}

int Server::accepting() {
    struct sockaddr_in ClientAddr;
    client_length = sizeof(ClientAddr);
    new_socket_fd = accept(socket_fd, (struct sockaddr *) &ClientAddr, &o_ClientLen);

    if (new_socket_fd < 0) {
    	cout << "ERROR on accepting the connection" << endl;
        return -1;
    } else {
    	cout << "New Client Connected, ip: " << inet_ntoa(ClientAddr.sin_addr)
    			<< ", port: " << ntohs(ClientAddr.sin_port) << endl;
        return new_socket_fd;
    }
}

int Server::reading(int &__socket_fd, char (*__buf)[BUFFER_SIZE]) {
    //char cBuffer[BUFFER_SIZE];
    bzero(__buf, BUFFER_SIZE);
    int resp = read(__socket_fd, __buf, BUFFER_SIZE);
    if (resp < 0)
    	cout << "Error occurred while reading from socket" << endl;
    return resp;
}


bool Server::writing(int &__socket_fd, const string &__str) {
	int resp = write(__socket_fd, __str.c_str(), BUFFER_SIZE);

    if (resp < 0) {
    	cout << "Error occurred while writing to socket" << endl;
        return false;
    }
    return true;
}

void Server::start() {
    if (!binding())
        Helper::Error("Error on binding to port.\n");

    while (true) {
        FD_ZERO(&fd_read);
        FD_SET(socket_fd, &fd_read);

        delay.tv_sec = 1;
		delay.tv_usec = 0;

		if (max_fd < socket_fd)
            max_fd = socket_fd;

		int selecting = select(max_fd + 1, &fd_read, NULL, NULL, &delay);

        if (selecting > 0) {
            new_socket_fd = accepting();

            if (FD_ISSET(socket_fd, &fd_read) ) {
                char msg[] = "Welcome to Mega-Chat!.\n\n";

                if (send(new_socket_fd, msg, strlen(msg), 0) != strlen(msg))
                    perror("Cannot send.");

                fcntl(new_socket_fd, F_SETFL, fcntl(new_socket_fd, F_GETFL) | O_NONBLOCK);

                accepted_list.push_back(new_socket_fd);
                FD_SET(new_socket_fd, &fd_read);
            }
        }

        for (list<int>::iterator it = accepted_list.begin(); it != accepted_list.end(); it++) {
            FD_SET(*it, &fd_read);
            if (*it > 0 && max_fd < *it)
                max_fd = *it;
        }

        delay.tv_sec = 1;
		delay.tv_usec = 0;

		selecting = select(max_fd + 1, &fd_read, NULL, NULL, &delay);

        if (selecting > 0) {
            for (list<int>::iterator it = accepted_list.begin(); it != accepted_list.end(); it++) {
                if (FD_ISSET(*it, &fd_read)) {
                    char buf[BUFFER_SIZE];
                    int _read = reading(*it, &buf);

                    if (_read != 0) {
                        vector<string> tokens = Helper::Split(string(buf),' ');

                        if (tokens.size() == 2) {
                            string sItemName = vTokens[0];
                            double dAmount = atof(vTokens[1].c_str());
                            dAmount = o_DataCenter.BuyItem(sItemName.c_str(), dAmount);
                            printf("\nClient said : %s", cBuffer);
                            if ( Write(*it, Helper::ToString(dAmount)) ) {
                                if (dAmount == -1) {
                                    printf ("Invalid Order.\n");
                                } else if (dAmount == -2) {
                                    printf("Out of stock for %s\n", cBuffer);
                                } else {
                                    printf ("Calculated Amount : %f \n", dAmount);
                                }
                            } else {}
                        }
                        else if (vTokens.size() == 1)
                        {
                            string sString = vTokens[0];

                            if (sString.compare("stock\n") == 0)
                            {
                                sString = o_DataCenter.GetStock();
                                Write(*it, sString);
                                printf("\n");
                                o_DataCenter.PrintStock();
                            }
                            else
                            {
                                Write(*it, Helper::ToString(-1));
                            }
                        }
                        else
                        {
                            printf("Invalid Input.\n");
                        }

                    }
                    else
                    {
                        printf("Client disconnected.\n");
                        close(*it);
                        lst_AcceptedList.remove(*it);
                    }
                    break;
                }

            }
        }
    }

}

Server::~Server()
{
    close(i_NewSockFD);
    close(i_SockFD);
}
