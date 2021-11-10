
#include "CommandList.hpp"



int	CommandList::admin(std::vector<std::string> command, User user) {
	std::string adminInfo =		":" + Server::serverName + " 256 " + user.getNickname() + Server::serverName + " :Administrative info\n";
	std::string adminNickname =	":" + Server::serverName + " 258 " + user.getNickname() + " :Nickname		" + "TestNickname" + "\n";
	std::string adminName =		":" + Server::serverName + " 257 " + user.getNickname() + " :Name		" + "TestName" + "\n";
	std::string adminEmail =	":" + Server::serverName + " 259 " + user.getNickname() + " :E-Mail		" + "Test@test.com" + "\n";

	if (command.size() != 1)
	{
		if (command[1] != Server::serverName) {
			std::string resultString = ":IRCat 402 " + user.getNickname() + " :No such server";
			Server::writing(user.getSocketFd(), resultString);
		} else {
			Server::writing(user.getSocketFd(), adminInfo);
			Server::writing(user.getSocketFd(), adminNickname);
			Server::writing(user.getSocketFd(), adminName);
			Server::writing(user.getSocketFd(), adminEmail);
		}
	} else {
		Server::writing(user.getSocketFd(), adminInfo);
		Server::writing(user.getSocketFd(), adminNickname);
		Server::writing(user.getSocketFd(), adminName);
		Server::writing(user.getSocketFd(), adminEmail);
	}
	return 1;
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














