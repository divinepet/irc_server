#pragma once
#include <iostream>
#include <string>
using namespace std;

class User;
class Service;

class Service {
public:
	static string getTime();
	static string getDate();
	static string formatMsg(int replyCode, const string msg, User& user);
	static string formatMsg(int replyCode, const string msg, User& user, string optional);
};

#include "../server/Server.hpp"