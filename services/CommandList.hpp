#pragma once

#include <vector>
#include "../server/Server.hpp"

class CommandList {
public:
	static void	admin(std::vector<std::string> args, User& user);
	static void nick(std::vector<std::string> args, User& user);
	static void info(std::vector<std::string> args, User& user);
	static void away(std::vector<std::string> args, User &user);
	static void invite(std::vector<std::string> args, User &user);
	static void pass(std::vector<std::string> args, User &user);
};
