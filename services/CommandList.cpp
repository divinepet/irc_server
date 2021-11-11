
#include "CommandList.hpp"

void	CommandList::admin(std::vector<std::string> command, User& user) {
	if (command.size() == 1 || (command.size() != 1 && command[1] == serverInfo::serverName)) {
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
}

void CommandList::away(std::vector<std::string> command, User &user) {
    if (command.size() == 1) {
        user.setAway(false);
        Server::writing(user.getSocketFd(), Service::formatMsg(305, "You are no longer marked as being away", user));
    }
    else if (command.size() > 1) {
        user.setAway(true);
		Server::writing(user.getSocketFd(), Service::formatMsg(306, "You have been marked as being away", user));
        user.setAutoReply(command[1]);
    }
    else
        return ;
}

void CommandList::invite(std::vector<std::string> command, User &user) {

    std::string requested_user;
    std::string channel_name;

    if (command.size() < 3) {
		Server::writing(user.getSocketFd(), Service::formatMsg(461, "Not enough parameters", user));
    }
    else {

    }
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

void	CommandList::ison(std::vector<std::string> args, User& user, std::list<User> userList) {

	std::string onlineUsers = "";

	if (args.size() == 1)
		Server::writing(user.getSocketFd(), Service::formatMsg(461, "Not enough parameters", user));
	else {
		for (std::list<User>::iterator userIt = userList.begin(); userIt != userList.end(); userIt++) {
			for (std::vector<std::string>::iterator strIt = args.begin(); strIt != args.end(); strIt++) {
				if (*strIt == userIt->getNickname()) {
					onlineUsers += userIt->getNickname();
					onlineUsers += " ";
				}
			}
		}
		onlineUsers.pop_back();
		Server::writing(user.getSocketFd(), Service::formatMsg(303, onlineUsers, user));
	}
}
