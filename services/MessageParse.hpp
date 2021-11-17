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
	static int defineCommandType(vector<string> &args, User& user, string pass);
public:
	static int handleMessage(string _msg, User& user, string pass="");
};
