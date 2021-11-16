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
	static void	emptyChannel(list<Channel> &channel_list);

<<<<<<< HEAD
    static pair<list<User>::iterator, bool>     isUserExist(list<User> users_list, string name);
    static pair<list<Channel>::iterator, bool>  isChannelExist(list<Channel> channels_list, string name);

=======
    static pair<list<User>::iterator, bool>     isInList(list<User>::iterator first, list<User>::iterator last, string name);
    static pair<list<Channel>::iterator, bool>  isInList(list<Channel>::iterator first, list<Channel>::iterator last, string name);
	static string	getUsersFromList(User &user, list<User> &userlist);
>>>>>>> origin/NAMES_cmd
private:
	static bool	channelIsEmpty(const Channel &channel);
    static bool isChannelName(string str);
	static bool	isComma(char c);
    static bool isNotComma(char c);

};

#include "../server/Server.hpp"
