#pragma once

#include <vector>
#include "../server/Server.hpp"

class CommandList
{
private:
	/* data */
public:
	CommandList(/* args */);
	~CommandList();

	static void	admin(std::vector<std::string> command, User user);

};
