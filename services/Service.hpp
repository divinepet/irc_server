#pragma once
#include "../server/Server.hpp"

using namespace std;

class User;

class Service {
public:
	static uint64_t timer();
	static string getDate();
	static vector<string> split(const string &str, char c);
	static void errMsg(int err, User &user, string arg1="", string arg2="");
	static void replyMsg(int code, User &user, string arg1="", string arg2="", string arg3="", string arg4="",
												string arg5="", string arg6="", string arg7="", string arg8="");
	static void sendMsg(User &sender, User& recipient, string arg1="", string arg2="", string arg3="");
	static bool channelIsEmpty(const Channel &channel);
    static pair<list<User>::iterator, bool>     isUserExist(string name);
    static pair<list<Channel>::iterator, bool>  isChannelExist(string name);
    static pair<list<User>::iterator, bool>     isUserExist(list<User> &users_list, string name);
    static pair<list<Channel>::iterator, bool>  isChannelExist(list<Channel> &channels_list, string name);
	static string	getUsersFromList(User &user, list<User> &userlist, Channel &channel);
	static void		deleteChannelFromUser(User &user, Channel &channel);
	static void sendFile(const string& server_info);
	static string to_string(list<User> lst, Channel &channel);
	static string to_string(list<User> lst, bool isOperList);
	static bool	match(char *s1, char *s2);
    static bool isChannelName(string str);
private:
	static bool	isComma(char c);
    static bool isNotComma(char c);
	static bool	isStar(char c);
	static bool isNotStar(char c);
	static bool	isEnter(char c);
	static bool isNotEnter(char c);
	static bool isSpace(char c);
	static bool isNotSpace(char c);
};

#include "../server/Server.hpp"
