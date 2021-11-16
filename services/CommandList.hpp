#pragma once

#include <vector>
#include "../server/Server.hpp"

class Channel;

class CommandList {
public:
	static void	admin_cmd(vector<string> args, User& user);
	static void away_cmd(vector<string> args, User &user);
	static void info_cmd(vector<string> args, User& user);
	static void invite_cmd(vector<string> args, User &user, list<User> user_list, list<Channel> &channel_list);
	static void ison_cmd(vector<string> args, User& user, list<User> userList);
	static void join_cmd(vector<string> args, User &user, list<Channel> &channel_list);
	static void kick_cmd(vector<string> args, User &user, list<Channel> &channel_list);
	static void kill_cmd(vector<string> args, User &user, list<User> &user_list);
	static void	list_cmd(vector<string> args, User &user, list<Channel> &channel_list);
//	static void mode_cmd(vector<string> args, User &user, list<User> &user_list, list<Channel> &channel_list);
	static void motd(User& user);
	static int nick_cmd(vector<string> args, User& user, list<User> &userList);
	static void oper_cmd(vector<string> args, User& oper);
	static void part_cmd(vector<string> args, User &user, list<Channel> &channel_list);
//	static void pass_cmd(vector<string> args, User &user, list<User>& userList, string pass);
	static int ping_cmd(vector<string> args, User &user);
	static int pong_cmd(vector<string> args, User &user);
	static void privmsg_cmd(vector<string> args, User &user, list<User> user_list, list<Channel> channel_list);
	static int restart_cmd(User &user);
	static void rehash_cmd(User &user);
	static void time_cmd(vector<string> args, User &user);
//	static int user_cmd(vector<string> args, User &user);
	static void version_cmd(vector<string> args, User &user);

//	static bool checkModeParams(vector<string> args, User &user);
//	static bool checkModeFlags(string flags_str, User &user, int &params_num);
};
