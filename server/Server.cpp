#include "Server.hpp"

Server::Server(int _port, string _pass) {
    if (_port > 1023 && _port < 49152) {
        initialize(_port, _pass);
        cout << "Server will be bound to port: " << _port << endl;
    } else
		throw "Wrong port!";
}

void Server::initialize(int _port, string& _pass) {
    port = _port;
	pass = _pass;
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
	User user(new_socket_fd);

    if (new_socket_fd < 0) {
    	cout << "ERROR on accepting the connection" << endl;
		new_socket_fd = -1;
    } else {

    	cout << "New Client Connected, ip: " << inet_ntoa(ClientAddr.sin_addr)
    			<< ", port: " << ntohs(ClientAddr.sin_port) << endl;
    }
	if (FD_ISSET(socket_fd, &fd_read) ) {
		fcntl(new_socket_fd, F_SETFL, fcntl(new_socket_fd, F_GETFL) | O_NONBLOCK);

		user.setRealHost(inet_ntoa(ClientAddr.sin_addr));
		users_list.push_back(user);
		FD_SET(new_socket_fd, &fd_read);
	}
	return new_socket_fd;
}

int Server::reading(const int &_socket_fd, char (*_buf)[BUFFER_SIZE]) {
    bzero(_buf, BUFFER_SIZE);
    int resp = recv(_socket_fd, _buf, BUFFER_SIZE, 0);
    if (resp < 0)
    	cout << "Error occurred while reading from socket" << endl;
    return resp;
}

bool Server::writing(int _client_socket, const string &_str) {
	int resp = send(_client_socket, _str.c_str(), strlen(_str.c_str()), 0);

    if (resp < 0) {
    	cout << "Error occurred while writing to socket" << endl;
        return false;
    }
    return true;
}

void Server::get_message() {
	for (list<User>::iterator it = users_list.begin(); it != users_list.end(); it++) {
		if (FD_ISSET(it->getSocketFd(), &fd_read)) {
			char buf[BUFFER_SIZE];
			int _read = reading(it->getSocketFd(), &buf);

			if (_read != 0) {
				int code = MessageParse::handleMessage(buf, *it, users_list, pass, channel_list);
				switch (code) {
					case 3: restartServer(); break;
					default: ;
				}
			} else {
				printf("%s disconnected.\n", it->getNickname().c_str());
				close(it->getSocketFd());
				users_list.remove(*it);
                Service::emptyChannel(channel_list);
			}
			break;
		}

	}
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

        if (selecting > 0)
            new_socket_fd = accepting();

        for (list<User>::iterator it = users_list.begin(); it != users_list.end(); it++) {
            FD_SET(it->getSocketFd(), &fd_read);
            if (it->getSocketFd() > 0 && max_fd < it->getSocketFd())
            	max_fd = it->getSocketFd();
        }

        delay.tv_sec = 0;
        delay.tv_usec = 0;

		selecting = select(max_fd + 1, &fd_read, NULL, NULL, &delay);

        if (selecting > 0)
            get_message();
    }

}

void Server::restartServer() {
	this->~Server();
	system("clear");
	start();
}

Server::~Server() {
	for (list<User>::iterator it = users_list.begin(); it != users_list.end(); it++)
		close(it->getSocketFd());
    close(socket_fd);
}

