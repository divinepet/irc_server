#pragma once

#include <iostream>
#include "../server/Server.hpp"
using namespace std;

#define f(a) msg.find(a) != string::npos

class User;

class Bot {
	static char asciitolower(char in);
public:
	Bot();
	virtual ~Bot();
	static void generateAnswer(User &user, string msg, const string& cmd, const string& ch_name);
};
