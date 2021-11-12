#pragma once

#include <vector>
#include "../server/Server.hpp"

class Channel;

class CommandList {
public:
	static void	admin(std::vector<std::string> args, User& user);
	static void motd(User& user);
	static void nick(std::vector<std::string> args, User& user, list<User> &userList);
	static void info(std::vector<std::string> args, User& user);
	static void ison(std::vector<std::string> args, User& user, list<User> userList);
	static void away(std::vector<std::string> args, User &user);
	static void invite(std::vector<std::string> args, User &user, list<User> user_list, list<Channel> &channel_list);
//	static void pass(vector<string> args, User &user, list<User>& userList, string pass);
	static void join(vector<string> args, User &user, list<Channel> &channel_list);
//	static void user(std::vector<std::string> args, User &user);
	static void part(std::vector<std::string> args, User &user, list<Channel> &channel_list);
	static void time(std::vector<std::string> args, User &user);
	static void version(std::vector<std::string> args, User &user);
	static int restart(User &user);
	static void kick(vector<string> args, User &user, list<Channel> &channel_list);
	static void kill(vector<string> args, User &user, list<User> &user_list);
};
