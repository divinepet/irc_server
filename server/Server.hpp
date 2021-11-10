#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "../services/MessageParse.hpp"

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 5000

using namespace std;

class Server {
private:
    int port;
    int socket_fd, new_socket_fd;
    socklen_t client_length;
    int max_fd;
    fd_set fd_accept;
    fd_set fd_read;
    fd_set fd_write;
    timeval delay;
public:
    list<User> users_list;
    static string serverName;

private:
    void initialize(int __port);
    bool binding();
    int accepting();
    int reading(const int &__socket_fd, char (*__buf)[BUFFER_SIZE]);
    void get_message();
public:
    Server();
    Server(int __port);
    ~Server();
    void start();
    static bool writing(int __client_socket, const string &__str);
};

string Server::serverName = "Irccc";
