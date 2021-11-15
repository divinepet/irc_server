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
    listen(socket_fd, atoi(config["maxConnections"].c_str()));

    fcntl(socket_fd, F_SETFL, O_NONBLOCK);

    max_fd = socket_fd;
    return true;
}

pair<int, string> Server::accepting() {
    struct sockaddr_in ClientAddr;
    client_length = sizeof(ClientAddr);
    new_socket_fd = accept(socket_fd, (struct sockaddr *) &ClientAddr, &client_length);
    if (new_socket_fd < 0) {
    	cout << "ERROR on accepting the connection" << endl;
        return make_pair(-1, nullptr);
    }
	cout << "New Client Connected, ip: " << inet_ntoa(ClientAddr.sin_addr)
			<< ", port: " << ntohs(ClientAddr.sin_port) << endl;
	return make_pair(new_socket_fd, inet_ntoa(ClientAddr.sin_addr));
}

int Server::reading(const int &_socket_fd, char (*_buf)[BUFFER_SIZE]) {
	bzero(_buf, BUFFER_SIZE);
	int resp = recv(_socket_fd, _buf, BUFFER_SIZE, 0);
	return (resp < 0) ? cout << "Error occurred while reading from socket" << endl, resp : resp;
}

bool Server::writing(int _client_socket, const string &_str) {
	int resp = send(_client_socket, _str.c_str(), strlen(_str.c_str()), 0);
	return resp >= 0 || (cout << "Error occurred while writing to socket" << endl, false);
}

void* ping_request(void *_ping_data) {
	size_t request_timeout = atoi(config["requestTimeout"].c_str()) * 1000;
	t_ping* p_d = ((t_ping *)_ping_data);
	time_t time_now = Service::timer();
	p_d->restart_response = false;
	while (time_now - p_d->last_message_time < request_timeout) {
		if (p_d->restart_request) {
			p_d->restart_request = false;
			p_d->last_message_time = Service::timer();
		}
		time_now = Service::timer();
	}
	pthread_mutex_lock(&p_d->print_mutex);
	if (!Server::writing(p_d->client_socket,
					":" + config["server.name"] + " PING :" + config["server.name"] + "\n"))
		return NULL;
	pthread_mutex_unlock(&p_d->print_mutex);
	p_d->response_waiting = true;
	time_now = Service::timer();
	time_t response_time = Service::timer();
	size_t response_timeout = atoi(config["responseTimeout"].c_str()) * 1000;
	while ((time_now - response_time < response_timeout) && !p_d->restart_response) {
		time_now = Service::timer();
	}
	if (!p_d->restart_response) {
		close(p_d->client_socket);
		list<User> *v;
		v = reinterpret_cast<list<User>*>(p_d->users_list_ptr);
		cout << p_d->client_socket << endl;
		for (list<User>::iterator it = v->begin(); it != v->end() ; ++it) {
			if (it->getSocketFd() == p_d->client_socket) {
				v->erase(it);
				break;
			}
		}
	}
	p_d->response_waiting = false;
	return NULL;
}

void Server::get_message() {
	for (list<User>::iterator it = users_list.begin(); it != users_list.end(); it++) {
		if (FD_ISSET(it->getSocketFd(), &fd_read)) {
			char buf[BUFFER_SIZE];
			int _read = reading(it->getSocketFd(), &buf);

			if (_read != 0) {
				message_poll += buf;
				if (!strstr(buf, "\n"))
					continue;
				if (it->isRegistered() && !rr_data[it->getId()].response_waiting)
					rr_data[it->getId()].restart_request = true;
				int code = MessageParse::handleMessage(message_poll, *it,
													users_list,pass, channel_list);
				message_poll.clear();
				switch (code) {
					case 3: restartServer(); break;
					case 7: {
						if (rr_data[it->getId()].last_message_time == -1) {
							rr_data[it->getId()].last_message_time = Service::timer();
							pthread_create(&request_thread[it->getId()], NULL, &ping_request, &rr_data[it->getId()]);
						}
						break;
					}
					case 8: {
						if (!rr_data[it->getId()].response_waiting)
							rr_data[it->getId()].restart_request = true;
						else {
							rr_data[it->getId()].restart_response = true;
							rr_data[it->getId()].last_message_time = Service::timer();
							pthread_create(&request_thread[it->getId()], NULL, &ping_request, &rr_data[it->getId()]);
						}
						break;
					}
					default:;
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
	int maxClients = atoi(config["maxConnections"].c_str());
	rr_data = new t_ping[maxClients];
	request_thread = new pthread_t[maxClients];
	rr_data->users_list_ptr = reinterpret_cast<uintptr_t>(&users_list);
	pthread_mutex_init(&rr_data->print_mutex, NULL);

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

		int selecting = select(max_fd + 1, &fd_read, &fd_write, NULL, &delay);

        if (selecting > 0) {
			pair<int, string> pair = accepting();
            new_socket_fd = pair.first;
            if (FD_ISSET(socket_fd, &fd_read) ) {
                fcntl(new_socket_fd, F_SETFL, O_NONBLOCK);

                User user(new_socket_fd);
				user.setRealHost(pair.second);
				rr_data[user.getId()].client_socket = new_socket_fd;
				rr_data[user.getId()].last_message_time = -1;
                users_list.push_back(user);

                FD_SET(new_socket_fd, &fd_read);
            }
        }

        for (list<User>::iterator it = users_list.begin(); it != users_list.end(); it++) {
            FD_SET(it->getSocketFd(), &fd_read);
            if (it->getSocketFd() > 0 && max_fd < it->getSocketFd())
            	max_fd = it->getSocketFd();
        }

        delay.tv_sec = 0;
        delay.tv_usec = 0;

		selecting = select(max_fd + 1, &fd_read, &fd_write, NULL, &delay);

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

