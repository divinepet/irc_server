#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sys/time.h>

#include "../server/Server.hpp"

using namespace std;

class User;

class Service {
public:
	static time_t timer();
	static string getDate();
	static vector<string> split(const string &str, char c);
	static void errMsg(int err, User &user, string arg1="", string arg2="");
	static void replyMsg
	(int code, User &user, string arg1="", string arg2="", string arg3="", string arg4="",
												string arg5="", string arg6="", string arg7="", string arg8="");
	static void sendMsg(int code, User &sender, User& recipient,
												string arg1="", string arg2="", string arg3="", string arg4="");
	static bool channelIsEmpty(const Channel &channel);
    static pair<list<User>::iterator, bool>     isUserExist(string name);
    static pair<list<Channel>::iterator, bool>  isChannelExist(string name);
    static pair<list<User>::iterator, bool>     isUserExist(list<User> &users_list, string name);
    static pair<list<Channel>::iterator, bool>  isChannelExist(list<Channel> &channels_list, string name);
	static string	getUsersFromList(User &user, list<User> &userlist);
	static void		deleteChannelFromUser(User &user, Channel &channel);
	static void sendFile(User &sender, string &recipient, const string& fileName);
private:
    static bool isChannelName(string str);
	static bool	isComma(char c);
    static bool isNotComma(char c);

};

#include "../server/Server.hpp"
