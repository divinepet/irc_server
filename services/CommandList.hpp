#pragma once

#include <vector>
#include "../server/Server.hpp"

class CommandList {
public:
	static void	admin(std::vector<std::string> command, User& user);
	static void nick(std::vector<std::string> args, User& user);
	static void info(std::vector<std::string> args, User& user);
};
