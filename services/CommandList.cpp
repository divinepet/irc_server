
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

void CommandList::info(std::vector<std::string> args, User& user) {

	std::string compilationTime = "Compilation Time - " + std::string("[00:00:00]");
	std::string serverVersion = "Server Version - " + std::string("1.0");


	if (args.size() == 1 || (args.size() != 1 && args[1] == serverInfo::serverName)) {
		Server::writing(user.getSocketFd(), Service::formatMsg(371, ">| Server Information |<", user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(371, compilationTime, user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(371, serverVersion, user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(374,  "End of /INFO list", user, serverInfo::serverName));
	} else
		Server::writing(user.getSocketFd(), Service::formatMsg(402, "No such server", user));
}
