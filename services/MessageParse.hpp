#pragma once

#include "../server/Server.hpp"
#include "CommandList.hpp"

using namespace std;

class Channel;

class MessageParse {
	static void splitMessage(string _msg, vector<string> &args);
	static int defineCommandType(vector<string> &args, User& user, string pass, int socket);
public:
    static int handleMessage(string _msg, User& user, int socket, string pass="");
};
