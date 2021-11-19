#pragma once

#include <list>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include "../models/User.hpp"
#include "../models/Channel.hpp"
#include "../services/MessageParse.hpp"
#include "../services/Service.hpp"
#include "../services/YamlParser.hpp"
#include "../services/sha256.hpp"

#define BUFFER_SIZE 512

static YamlParser config;

typedef struct s_ping {
	uint64_t last_message_time;
	int client_socket;
	bool response_waiting;
	bool restart_request;
	bool restart_response;
	bool isOnline;
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
public:
    static uint64_t response_timeout;
    static uint64_t request_timeout;
    static t_ping *rr_data;
    static list<User> userList;
    static list<User> userHistory;
    static list<Channel> channelList;


private:
	void initialize(int _port, string& _pass);
	bool binding();
	pair<int, string> accepting();
	int reading(const int &_socket_fd, char (*_buf)[BUFFER_SIZE]);
	void get_message(char *buf, User &user);
	void restartServer();
	void createThread(User &user);
public:
	Server(int _port, string _pass);
	~Server();
	void start();
	static bool writing(int _client_socket, const string& _str);
	static void kickUser(User& user);
};
