#pragma once

#include <vector>
#include "../server/Server.hpp"

class Channel;
class User;
using namespace std;

class CommandList {
public:
	static void	adminCmd(vector<string> args, User& user);
	static void awayCmd(vector<string> args, User &user);
	static void infoCmd(vector<string> args, User& user);
	static void inviteCmd(vector<string> args, User &user, list<User> userList, list<Channel> &channelList);
	static void isonCmd(vector<string> args, User& user, list<User> userList);
	static void joinCmd(vector<string> args, User &user, list<Channel> &channelList);
	static void kickCmd(vector<string> args, User &user, list<User> &userList, list<Channel> &channelList);
	static void killCmd(vector<string> args, User &user, list<User> &userList);
	static void	listCmd(vector<string> args, User &user, list<Channel> &channelList);
//	static void modeCmd(vector<string> args, User &user, list<User> &userList, list<Channel> &channelList);
	static void motd(User& user);
	static void	namesCmd(vector<string> args, User &user, list<User> &userList, list<Channel> &channelList);
	static int nickCmd(vector<string> args, User& user, list<User> &userList);
	static void noticeCmd(vector<string> args, User &user, list<User> userList, list<Channel> channelList);
	static void operCmd(vector<string> args, User& oper);
	static void partCmd(vector<string> args, User &user, list<User> &userList, list<Channel> &channelList);
//	static void passCmd(vector<string> args, User &user, list<User>& userList, string pass);
	static int pingCmd(vector<string> args, User &user);
	static int pongCmd(vector<string> args, User &user);
	static void privmsgCmd(vector<string> args, User &user, list<User> userList, list<Channel> channelList, bool isNotice);
	static int restartCmd(User &user);
	static void rehashCmd(User &user);
	static void timeCmd(vector<string> args, User &user);
//	static int userCmd(vector<string> args, User &user);
	static void versionCmd(vector<string> args, User &user);

//	static bool checkModeParams(vector<string> args, User &user);
//	static bool checkModeFlags(string flags_str, User &user, int &params_num);
};
