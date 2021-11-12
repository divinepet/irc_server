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
	static void pass(std::vector<std::string> args, User &user);
	static void join(std::vector<std::string> args, User &user, list<Channel> &channel_list);
	static void user(std::vector<std::string> args, User &user);

private:
    static std::vector<std::string> split(std::string str, char ch); // not full-tested
};
