
#include "CommandList.hpp"

void	CommandList::admin(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == serverInfo::serverName)) {
		Service::replyMsg(256, user, serverInfo::serverName);
		Service::replyMsg(257, user, "Test");
		Service::replyMsg(258, user, "Test");
		Service::replyMsg(259, user, "Test@test.com");
	} else
		Service::errMsg(402, user, args[1]);
}

void CommandList::motd(User &user) {
	std::ifstream infile("daily");
	std::string dailyMessageLine;
	Service::replyMsg(375, user, serverInfo::serverName);
	while (std::getline(infile, dailyMessageLine))
		Service::replyMsg(372, user, dailyMessageLine);
	Service::replyMsg(376, user);
}

void CommandList::nick(std::vector<std::string> args, User& user) {
	if (args.size() == 1) {
		Service::errMsg(461, user);
		return;
	}
	user.setNickname(args[1]);
	user.setRegisterPhase(user.getRegisterPhase() + 1);
	if (user.getRegisterPhase() == 3 && user.isValidPass()) motd(user);
}

void CommandList::away(std::vector<std::string> args, User &user) {
    if (args.size() == 1) {
        user.setAway(false);
		Service::replyMsg(305, user);
    }
    else if (args.size() > 1) {
        user.setAway(true);
		Service::replyMsg(306, user);
        user.setAutoReply(args[1]);
    }
    else
        return ;
}

void CommandList::invite(std::vector<std::string> args, User &user) {

    std::string requested_user;
    std::string channel_name;

    if (args.size() < 3) {
		Service::errMsg(461, user);
    }
    else {

    }
}

void CommandList::info(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == serverInfo::serverName)) {
		Service::replyMsg(371, user, ">| Server Information |<");
		Service::replyMsg(371, user, "Compilation Time" + serverInfo::compileTime);
		Service::replyMsg(371, user, "Server Version" + serverInfo::serverVersion);
		Service::replyMsg(374, user);
	} else
		Service::errMsg(402, user, args[1]);
}

void CommandList::pass(std::vector<std::string> args, User &user, std::list<User>& userList, string pass) {
	if (user.isRegistered()) {
		Service::errMsg(462, user);
		return;
	} else if (user.getRegisterPhase() == 2) {
		close(user.getSocketFd());
		userList.remove(user);
		return;
	}
	cout << pass << endl;
	if (args[1] == pass) {
		cout << "valid" << endl;
		user.setValidPass(true);
		user.setRegisterPhase(user.getRegisterPhase() + 1);
	}
}

void	CommandList::ison(std::vector<std::string> args, User& user, std::list<User> userList) {

	std::string onlineUsers = "";

	if (args.size() == 1)
		Service::errMsg(461, user);
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
		Service::replyMsg(303, user, onlineUsers);
	}
}

void CommandList::user(std::vector<std::string> args, User &user) {
	if (args.size() < 4) {
		Service::errMsg(461, user);
		return;
	}
	user.setUsername(args[1]);
	user.setHost(args[2]);
	user.setServername(args[3]);
	user.setRealname(args[4]);
	user.setRegisterPhase(user.getRegisterPhase() + 1);
	if (user.getRegisterPhase() == 3 && user.isValidPass()) motd(user);
}



//  JOIN #foo,#bar fubar,foobar

void CommandList::join(std::vector<std::string> args, User &user, list<Channel> &channel_list) {

    list<Channel>::iterator ch = channel_list.begin();

    if (args.size() > 1) {

        for (; ch != channel_list.end() && ch->_channel_name != args[1]; ++ch) {}
        if (ch != channel_list.end()) {
            channel_list.push_back(Channel(args[1], user));
        }
        else {
            ch->addUser(user);
        }
    }
}

// not full-tested
std::vector<std::string> CommandList::split(std::string str, char ch) {

    std::vector<std::string> result;

    for (size_t i = 0, j = str.find(ch, i); j != std::string::npos;) {
        result.push_back(str.substr(i,j - i));
        i = j + 1;
        j = str.find(ch, i);
        if (i != str.length() && j == std::string::npos) {
            result.push_back(str.substr(i, str.length()));
        }
    }

    return result;
}

