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

#define BUFFER_SIZE 1024
#define DEFAULT_PORT 5000

using namespace std;

class Server {
    int port;
    int socket_fd, new_socket_fd;
    socklen_t client_length;
    int max_fd;
    fd_set fd_accept;
    fd_set fd_read;
    fd_set fd_write;
    timeval delay;
    list<int> accepted_list;

    void initialize(int __port);
    bool binding();
    int accepting();
    int reading(int &__socket_fd, char (*__buf)[BUFFER_SIZE]);
    void get_message();
    bool writing(int &__socket_fd, const string &__str);
public:
    Server();
    Server(int __port);
    ~Server();
    void start();
};