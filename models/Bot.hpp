#pragma once

#include <iostream>
#include "../server/Server.hpp"
using namespace std;

#define f1(a) msg.find(a) != string::npos
#define f2(a,b) f1(a) || f1(b)
#define f3(a,b,c) f1(a) || f1(b) || f1(c)

class User;

class Bot {
	static char asciitolower(char in);
public:
	Bot();
	virtual ~Bot();
	static void generateAnswer(User &user, string msg, const string& cmd, const string& ch_name);
};
