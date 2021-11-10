#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../server/Server.hpp"

using namespace std;

class MessageParse {
	static void splitMessage(char *__buf, vector<string> &args);
	static int defineCommandType(vector<string> &args, User& user);
public:
	static void handleMessage(char *__buf, User& user);
};