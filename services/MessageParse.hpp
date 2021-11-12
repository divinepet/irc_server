#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../server/Server.hpp"
#include "CommandList.hpp"

using namespace std;

class Channel;

class MessageParse {
	static void splitMessage(char *_buf, vector<string> &args);
	static void defineCommandType(vector<string> &args, User& user, list<User>& users_list, string pass, list<Channel> &channel_list);
public:
	static void handleMessage(char *_buf, User& user, list<User>& users_list, string pass, list<Channel> &channel_list);
};
