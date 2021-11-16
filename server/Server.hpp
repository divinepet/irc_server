#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <list>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "../models/User.hpp"
#include "../models/Channel.hpp"
#include "../services/MessageParse.hpp"
#include "../services/Service.hpp"
#include "../services/YamlParser.hpp"
#include "../services/sha256.hpp"

#define BUFFER_SIZE 512

static YamlParser config;

typedef struct s_ping {
	time_t last_message_time;
	int client_socket;
	bool response_waiting;
	bool restart_request;
	bool restart_response;
	pthread_mutex_t print_mutex;
} t_ping;

using namespace std;

class Server {
private:
	int port, socket_fd, new_socket_fd, max_fd;
	string pass, message_poll;
    socklen_t client_length;
    fd_set fd_accept, fd_read, fd_write;
    timeval delay;
    t_ping *rr_data;
    pthread_t *request_thread;
public:
    static list<User> userList;
    static list<Channel> channelList;


private:
    void initialize(int _port, string& _pass);
    bool binding();
	pair<int, string> accepting();
    int reading(const int &_socket_fd, char (*_buf)[BUFFER_SIZE]);
    void get_message();
	void restartServer();
public:
    Server(int _port, string _pass);
    ~Server();

	void start();
    static bool writing(int _client_socket, const string& _str);
    static void kickUser(User user);
};
