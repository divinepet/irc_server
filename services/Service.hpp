#pragma once
#include <iostream>
#include "../server/Server.hpp"

using namespace std;

class Service {
public:
	static string getTime();
	static string formatMsg(int replyCode, const string msg, User& user);
	static string formatMsg(int replyCode, const string msg, User& user, string optional);
};