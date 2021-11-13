#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../server/Server.hpp"
#include "CommandList.hpp"

using namespace std;

class Channel;

class MessageParse {
	static void splitMessage(string _msg, vector<string> &args);
	static int defineCommandType(vector<string> &args, User& user, list<User>& users_list, string pass, list<Channel> &channel_list);
public:
	static int handleMessage(string _msg, User& user, list<User>& users_list, string pass, list<Channel> &channel_list);
};
