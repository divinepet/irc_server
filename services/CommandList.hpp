#pragma once

#include <vector>
#include "../server/Server.hpp"

class CommandList {
public:
	static int	admin(std::vector<std::string> command, User user);

};
