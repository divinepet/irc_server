#pragma once

#include <vector>
#include "../server/Server.hpp"

class Channel;
class User;
using namespace std;

class CommandList {
public:
	static void	admin(vector<string> args, User& user);
	static void away(vector<string> args, User &user);
	static void join(vector<string> args, User &user, list<Channel> &channel_list);
	static void info(vector<string> args, User& user);
	static void invite(vector<string> args, User &user, list<User> user_list, list<Channel> &channel_list);
	static void ison(vector<string> args, User& user, list<User> userList);
	static void kick(vector<string> args, User &user, list<Channel> &channel_list);
	static void kill(vector<string> args, User &user, list<User> &user_list);
	static void motd(User& user);
	static int nick(vector<string> args, User& user, list<User> &userList);
	static void oper(vector<string> args, User& oper);
	static void part(vector<string> args, User &user, list<Channel> &channel_list);
//	static void pass(vector<string> args, User &user, list<User>& userList, string pass);
	static int ping(vector<string> args, User &user);
	static int pong(vector<string> args, User &user);
	static int restart(User &user);
	static void time(vector<string> args, User &user);
//	static int user(vector<string> args, User &user);
	static void version(vector<string> args, User &user);
	static void mode(vector<string> args, User &user, list<User> &user_list, list<Channel> &channel_list);
	static bool checkModeParams(vector<string> args, User &user);
//	static bool checkModeFlags(string flags_str, User &user, int &params_num);
	static void	list_cmd(vector<string> args, User &user, list<Channel> &channel_list);
	static void	names(vector<string> args, User &user, list<Channel> &channel_list);

};
