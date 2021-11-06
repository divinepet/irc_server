#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFER_SIZE 1024
#define DEFAULT_SERVER "127.0.0.1"
#define DEFAULT_PORT 5000

using namespace std;

class Client {
	const char* host;
	int port;
	int socket_fd;
	struct sockaddr_in s_serverAddr;
	struct hostent *s_server;
public:
    Client();
    Client(const char* __host, int __port);
    ~Client();

    bool connecting();
    string reading();
    bool writing(const string &__str);
    bool writing(const char* __str);
};

