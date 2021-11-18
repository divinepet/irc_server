#include "Server.hpp"

list<User> Server::userList;
list<Channel> Server::channelList;
t_ping* Server::rr_data;
list<User> Server::userHistory;

Server::Server(int _port, string _pass) {
	if (_port < 1024 || _port > 49151)
		throw "Wrong port!";
	initialize(_port, _pass);
	cout << "Server will be bound to port: " << _port << endl;
}

void Server::initialize(int _port, string& _pass) {
    port = _port;
	pass = _pass;
    FD_ZERO(&fd_accept);
    FD_ZERO(&fd_read);
    FD_ZERO(&fd_write);
    delay.tv_sec = 0;
    delay.tv_usec = 0;
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
	t_ping* p_d = ((t_ping *)_ping_data);
	pthread_mutex_lock(&p_d->print_mutex);
	size_t request_timeout = atoi(config["requestTimeout"].c_str()) * 1000;
	pthread_mutex_unlock(&p_d->print_mutex);
	time_t time_now = Service::timer();
	p_d->restart_response = false;
	while (time_now - p_d->last_message_time < request_timeout) {
		if (!p_d->isOnline) return NULL;
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
	pthread_mutex_lock(&p_d->print_mutex);
	size_t response_timeout = atoi(config["responseTimeout"].c_str()) * 1000;
	pthread_mutex_unlock(&p_d->print_mutex);
	while ((time_now - response_time < response_timeout) && !p_d->restart_response) {
		if (!p_d->isOnline) return NULL;
		time_now = Service::timer();
	}
	if (!p_d->restart_response) {
		pthread_mutex_lock(&p_d->print_mutex);
		for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end() ; ++it) {
			if (it->getSocketFd() == p_d->client_socket) {
				pthread_mutex_lock(&p_d->print_mutex);
				Server::kickUser(*it);
				pthread_mutex_unlock(&p_d->print_mutex);
				break;
			}
		}
		pthread_mutex_unlock(&p_d->print_mutex);
	}
	p_d->response_waiting = false;
	return NULL;
}

void Server::get_message(char *buf, User& user) {
	message_poll += buf;
	if (!strstr(buf, "\r\n"))
		return;
	if (user.isRegistered() && !rr_data[user.getId()].response_waiting) {
		rr_data[user.getId()].restart_request = true;
	}
//	cout << "\"" << message_poll << "\"" << " -> MESSAGE POLL" << endl;
//	vector<string> cmdVector = Service::split(message_poll, '\n');
//	for (size_t i = 0; i < cmdVector.size(); i++) {
//		int code = MessageParse::handleMessage(cmdVector[i], user, pass);
		int code = MessageParse::handleMessage(message_poll, user, pass);
		message_poll.clear();
		switch (code) {
			case 3: restartServer(); break;
			case 7: {
				if (rr_data[user.getId()].last_message_time == -1) {
					rr_data[user.getId()].last_message_time = Service::timer();
					pthread_create(&request_thread[user.getId()], NULL, &ping_request, &rr_data[user.getId()]);
				} break;
			}
			case 8: {
				if (!rr_data[user.getId()].response_waiting) {
					rr_data[user.getId()].restart_request = true;
				}
				else {
					rr_data[user.getId()].restart_response = true;
					rr_data[user.getId()].last_message_time = Service::timer();
					pthread_create(&request_thread[user.getId()], NULL, &ping_request, &rr_data[user.getId()]);
				} break;
			} default:;
		}
//	}
//	message_poll.clear();
}

void Server::start() {
	int maxClients = atoi(config["maxConnections"].c_str());
	rr_data = new t_ping[maxClients];
	request_thread = new pthread_t[maxClients];
	pthread_mutex_init(&rr_data->print_mutex, NULL);

	if (!binding()) {
		perror("Error on binding to port.\n");
		exit(-1);
	}

	while (true) {
		FD_ZERO(&fd_read);
		FD_SET(socket_fd, &fd_read);
		if (max_fd < socket_fd)
			max_fd = socket_fd;
		if (select(max_fd + 1, &fd_read, &fd_write, NULL, &delay) > 0) {
			pair<int, string> pair = accepting();
			new_socket_fd = pair.first;
			if (FD_ISSET(socket_fd, &fd_read) ) {
				fcntl(new_socket_fd, F_SETFL, O_NONBLOCK);
				User user(new_socket_fd);
				user.setRealHost(pair.second);
				rr_data[user.getId()].client_socket = new_socket_fd;
				rr_data[user.getId()].isOnline = true;
				rr_data[user.getId()].last_message_time = -1;
				Server::userList.push_back(user);
				FD_SET(new_socket_fd, &fd_read);
			}
		}
		for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
			FD_SET(it->getSocketFd(), &fd_read);
			if (it->getSocketFd() > 0 && max_fd < it->getSocketFd())
				max_fd = it->getSocketFd();
		}
		if (select(max_fd + 1, &fd_read, &fd_write, NULL, &delay) > 0) {
			for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++)
				if (FD_ISSET(it->getSocketFd(), &fd_read)) {
					char buf[BUFFER_SIZE];
					(!reading(it->getSocketFd(), &buf)) ? kickUser(*it) : get_message(buf, *it);
					break;
				}
		}
	}
}

void Server::kickUser(User &user) {
	printf("%s disconnected.\n", user.getNickname().c_str());
	userHistory.push_back(user);
	for (list<Channel>::iterator it_ch = user.joinedChannels.begin(); it_ch != user.joinedChannels.end(); ++it_ch) {
		pair<list<Channel>::iterator, bool> pair = Service::isChannelExist(it_ch->getChannelName());
		if (pair.second) {
			/* Check for last operator */
			if (Service::isUserExist(pair.first->_operator_list, user.getNickname()).second
			&& pair.first->_operator_list.size() == 1 && pair.first->_userList.size() != 1) {
				User usr = *(++pair.first->_userList.begin());
				pair.first->addOperator(usr);
				Service::sendMsg(user, usr, "MODE", pair.first->getChannelName(), usr.getNickname() + " is operator now");
			}
			pair.first->deleteUser(user);
		}
		it_ch->deleteUser(user);
		list<User> lst = pair.first->getUserList();
		for (list<User>::iterator it_usr = lst.begin(); it_usr != lst.end(); ++it_usr) {
			Service::sendMsg(user, *it_usr, "QUIT", "Client exited");
		}
	}
	rr_data[user.getId()].isOnline = false;
	close(user.getSocketFd());
	Server::userList.remove(user);
	Server::channelList.remove_if(Service::channelIsEmpty);
}

void Server::restartServer() {
	this->~Server();
	system("clear");
	start();
}

Server::~Server() {
	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++)
		close(it->getSocketFd());
    close(socket_fd);
}

