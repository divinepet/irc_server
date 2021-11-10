
#include "CommandList.hpp"

//int	CommandList::admin(std::vector<std::string> command, User user) {
//
//	std::string serverName = "ASS";
//
//	std::string adminInfo =		":" + serverName + " 256 " + user.getNickname() + serverName + " :Administrative info\n";
//	std::string adminNickname =	":" + serverName + " 258 " + user.getNickname() + " :Nickname		" + "\n";
//	std::string adminName =		":" + serverName + " 257 " + user.getNickname() + " :Name		" + "\n";
//	std::string adminEmail =	":" + serverName + " 259 " + user.getNickname() + " :E-Mail		" + "\n";
//
//	if (command.size() != 1) {
//		if (command[1] != serverName) {
//			std::string resultString = ":IRCat 402 " + user.getNickname() + " :No such server\n";
//			Server::writing(user.getSocketFd(), resultString);
//		} else {
//			Server::writing(user.getSocketFd(), adminInfo);
//			Server::writing(user.getSocketFd(), adminNickname);
//			Server::writing(user.getSocketFd(), adminName);
//			Server::writing(user.getSocketFd(), adminEmail);
//		}
//	} else {
//		Server::writing(user.getSocketFd(), adminInfo);
//		Server::writing(user.getSocketFd(), adminNickname);
//		Server::writing(user.getSocketFd(), adminName);
//		Server::writing(user.getSocketFd(), adminEmail);
//	}
//	return 1;
//}

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
