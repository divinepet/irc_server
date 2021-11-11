
#include "CommandList.hpp"

void	CommandList::admin(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == serverInfo::serverName)) {
		Server::writing(user.getSocketFd(), Service::formatMsg(256, "Administrative info", user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(257,  "Nickname    TestNickname", user));
		Server::writing(user.getSocketFd(), Service::formatMsg(258,  "Name        TestName", user));
		Server::writing(user.getSocketFd(), Service::formatMsg(259,  "E-Mail      Test@test.com", user));
	} else
		Server::writing(user.getSocketFd(), Service::formatMsg(402, "No such server", user));
}

void CommandList::nick(std::vector<std::string> args, User& user) {
	if (args.size() == 1) {
		Server::writing(user.getSocketFd(), Service::formatMsg(461, "Not enough parameters", user));
		return;
	}
	user.setNickname(args[1]);
	std::ifstream infile("daily");
	std::string dailyMessageLine;
	Server::writing(user.getSocketFd(), Service::formatMsg(375, "- " + serverInfo::serverName + " Message of the day -", user));
	while (std::getline(infile, dailyMessageLine))
		Server::writing(user.getSocketFd(), Service::formatMsg(372, dailyMessageLine, user));
	Server::writing(user.getSocketFd(), Service::formatMsg(376, "End of /MOTD command", user));
}

void CommandList::away(std::vector<std::string> args, User &user) {
    if (args.size() == 1) {
        user.setAway(false);
        Server::writing(user.getSocketFd(), Service::formatMsg(305, "You are no longer marked as being away", user));
    }
    else if (args.size() > 1) {
        user.setAway(true);
		Server::writing(user.getSocketFd(), Service::formatMsg(306, "You have been marked as being away", user));
        user.setAutoReply(args[1]);
    }
    else
        return ;
}

void CommandList::invite(std::vector<std::string> args, User &user) {

    std::string requested_user;
    std::string channel_name;

    if (args.size() < 3) {
		Server::writing(user.getSocketFd(), Service::formatMsg(461, "Not enough parameters", user));
    }
    else {

    }
}

void CommandList::info(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == serverInfo::serverName)) {
		Server::writing(user.getSocketFd(), Service::formatMsg(371, ">| Server Information |<", user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(371, "Compilation Time - " + serverInfo::compileTime, user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(371, "Server Version - " + serverInfo::serverVersion, user, serverInfo::serverName));
		Server::writing(user.getSocketFd(), Service::formatMsg(374,  "End of /INFO list", user, serverInfo::serverName));
	} else
		Server::writing(user.getSocketFd(), Service::formatMsg(402, "No such server", user));
}

void CommandList::pass(std::vector<std::string> args, User &user) {

}
