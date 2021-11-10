
#include "CommandList.hpp"

void	CommandList::admin(std::vector<std::string> command, User& user) {
	if (command.size() != 1) {
		if (command[1] != serverInfo::serverName) {
			Server::writing(user.getSocketFd(), Service::formatMsg(402, "No such server", user));
			return;
		}
	} else {
		Server::writing(user.getSocketFd(), Service::formatMsg(256, "Administrative info", user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(257,  "Nickname    TestNickname", user));
		Server::writing(user.getSocketFd(), Service::formatMsg(258,  "Name        TestName", user));
		Server::writing(user.getSocketFd(), Service::formatMsg(259,  "E-Mail      Test@test.com", user));
	}
}

void CommandList::nick(std::vector<std::string> args, User& user) {
	if (args.size() == 1) {
		Server::writing(user.getSocketFd(), Service::formatMsg(461, "Not enough parameters", user));
		return;
	}
	user.setNickname(args[1]);
}
