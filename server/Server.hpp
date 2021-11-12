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

#define BUFFER_SIZE 1024

class Channel;

namespace serverInfo {
	static string serverName = "IrcServ";
	// static string compileTime = Service::getDate();
	static string serverVersion = "1.0";
};

using namespace std;

class Server {
private:
    int port;
	string pass;
    int socket_fd, new_socket_fd;
    socklen_t client_length;
    int max_fd;
    fd_set fd_accept;
    fd_set fd_read;
    fd_set fd_write;
    timeval delay;
public:
    list<User> users_list;
    list<Channel> channel_list;

private:
	Server();
    void initialize(int _port, string& _pass);
    bool binding();
    int accepting();
    int reading(const int &_socket_fd, char (*_buf)[BUFFER_SIZE]);
    void get_message();
public:
    Server(int _port, string _pass);
    ~Server();
    void start();
    static bool writing(int _client_socket, const string& _str);
};
