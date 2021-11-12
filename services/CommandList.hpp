#pragma once

#include <vector>
#include "../server/Server.hpp"

class Channel;

class CommandList {
public:
	static void	admin(std::vector<std::string> args, User& user);
	static void motd(User& user);
	static void nick(std::vector<std::string> args, User& user);
	static void info(std::vector<std::string> args, User& user);
	static void ison(std::vector<std::string> args, User& user, std::list<User> userList);
	static void away(std::vector<std::string> args, User &user);
	static void invite(std::vector<std::string> args, User &user);
	static void pass(vector<string> args, User &user, list<User>& userList, string pass);
	static void join(vector<string> args, User &user, list<Channel> &channel_list);
	static void user(std::vector<std::string> args, User &user);
};
