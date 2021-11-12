#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class User;
class Service;

class Service {
public:
	static string getTime();
	static string getDate();
	static vector<string> split(string str, char ch);
	static void errMsg(int err, User &user, string arg1="", string arg2="");
	static void replyMsg(int code, User &user, string arg1="", string arg2="", string arg3="", string arg4="",
												string arg5="", string arg6="", string arg7="", string arg8="");
    static bool isChannelName(string str);
};

#include "../server/Server.hpp"