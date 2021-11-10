#pragma once

#include <vector>
#include "../server/Server.hpp"

class CommandList {
public:
	static int	admin(std::vector<std::string> command, User user);
	static void away(std::vector<std::string> command, User &user);
	static void invite(std::vector<std::string> command, User &user);


};
