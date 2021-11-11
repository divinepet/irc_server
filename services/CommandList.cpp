
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

    std::string marked_msg = ":" + Server::serverName + " 306 " + user.getNickname()
                                    + " :You have been marked as being away";

    std::string unmarked_msg = ":" + Server::serverName + " 305 " + user.getNickname()
            + " :You are no longer marked as being away";

    if (command.size() == 1) {
        user.setAway(false);
        Server::writing(user.getSocketFd(), unmarked_msg);
    }
    else if (command.size() > 1) {
        user.setAway(true);
        Server::writing(user.getSocketFd(), marked_msg);
        user.setAutoReply(command[1]);
    }
    else
        return ;
}

void CommandList::invite(std::vector<std::string> command, User &user) {

    std::string requested_user;
    std::string channel_name;
    std::string err_msg = ":" + Server::serverName + " 461 " + user.getNickname()
            + " :Not enough parameters";

    if (command.size() < 3) {
        Server::writing(user.getSocketFd(), err_msg);
    }
    else {

    }
}














