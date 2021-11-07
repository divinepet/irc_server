#include "Server.hpp"

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

void Server::initialize(int __port) {
    port = __port;
    FD_ZERO(&fd_accept);
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    cout << "Server initialized" << endl;
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
    new_socket_fd = accept(socket_fd, (struct sockaddr *) &ClientAddr, &client_length);

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
    if (!binding()) {
        perror("Error on binding to port.\n");
    	exit(-1);
    }

    while (true) {
        FD_ZERO(&fd_read);
        FD_SET(socket_fd, &fd_read);

        delay.tv_sec = 0;
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

        delay.tv_sec = 0;
        delay.tv_usec = 0;

		selecting = select(max_fd + 1, &fd_read, NULL, NULL, &delay);

        if (selecting > 0) {
            for (list<int>::iterator it = accepted_list.begin(); it != accepted_list.end(); it++) {
                if (FD_ISSET(*it, &fd_read)) {
                    char buf[BUFFER_SIZE];
                    int _read = reading(*it, &buf);

                    if (_read != 0) {

                    	printf("user #%d: %s", *it, buf);
                    	string total_buf = "xxx #" + to_string(*it) + ": " + buf;
                    	for (list<int>::iterator i = accepted_list.begin(); i != accepted_list.end(); i++) {
                    		if (i == it)
								continue;
							if (send(*i, total_buf.c_str(), strlen(total_buf.c_str()), 0) != strlen(total_buf.c_str()))
								perror("Cannot send.");
						}
                    } else {
						printf("Client disconnected.\n");
						close(*it);
						accepted_list.remove(*it);
                    }
                    break;
                }

            }
        }
    }

}

Server::~Server() {
	for (list<int>::iterator it = accepted_list.begin(); it != accepted_list.end(); it++)
    	close(*it);
    close(socket_fd);
}
