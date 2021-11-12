
#include "CommandList.hpp"

void CommandList::admin(std::vector<std::string> args, User& user) {
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
//	user.setRegisterPhase(user.getRegisterPhase() + 1);
//	if (user.getRegisterPhase() == 3 && user.isValidPass()) motd(user);
	user.setValidPass(true);
	user.setRegisterPhase(3);
	motd(user);
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

void CommandList::invite(std::vector<std::string> args, User &user, list<User> user_list, list<Channel> &channel_list) {

    std::string msg;
    std::string rqsted_user;
    std::string rqsted_chnl_name;
    list<User>::iterator usr_iter = user_list.begin();
    list<Channel>::iterator chnl_iter = channel_list.begin();
    list<User>::iterator chnl_usr_list = chnl_iter->_user_list.begin();
    list<User>::iterator chnl_oper_list = chnl_iter->_operator_list.begin();

    if (args.size() > 2) {
        rqsted_user = args[1];
        rqsted_chnl_name = args[2];
        for (; chnl_iter != channel_list.end() && chnl_iter->_channel_name != rqsted_chnl_name; ++chnl_iter) {} // searching rqsted channel
        if (chnl_iter != channel_list.end()) { // if rqsted channel exists
            for (; usr_iter != user_list.end() && usr_iter->getNickname() != rqsted_user; ++usr_iter) {} // searching rqsted user
            if (usr_iter != user_list.end()) { // if rqsted user exists
                for (; chnl_usr_list != chnl_iter->_user_list.end()
                                && chnl_usr_list->getNickname() != user.getNickname(); ++chnl_usr_list) {} // searching current user on rqsted channel
                if (chnl_usr_list != chnl_iter->_user_list.end()) { // if current user on rqsted channel
                    chnl_usr_list = chnl_iter->_user_list.begin();
                    for (; chnl_usr_list != chnl_iter->_user_list.end()
                           && chnl_usr_list->getNickname() != rqsted_user; ++chnl_usr_list) {} // searching rqsted user on rqsted channel
                    if (chnl_usr_list == chnl_iter->_user_list.end()) { // if rqsted user NOT on rqsted channel
                        if (chnl_iter->_is_invite_only) { // if rqsted channel is invite only
                            for (; chnl_oper_list != chnl_iter->_operator_list.end()
                                                && chnl_oper_list->getNickname() != user.getNickname(); ++chnl_oper_list) {} // searching current user in operator list of rqsted channel
                            if (chnl_oper_list == chnl_iter->_operator_list.end()) { // cuurent user not operator on invite only channel
                                Service::errMsg(482, user,rqsted_chnl_name);
                                return ;
                            }
                        }
                        if (!usr_iter->isAway()) { // rqsted user is available
                            chnl_iter->_invite_list.push_back(*usr_iter);
                            msg = ":" + user.getNickname() + "!t127.0.0.1 INVITE" + rqsted_user + " :" +rqsted_chnl_name;
                            Server::writing(usr_iter->getSocketFd(), msg);
                            Service::replyMsg(341, user, rqsted_chnl_name, rqsted_user);
                        } else { // rqsted user has AWAY status
                            Service::replyMsg(301, user, rqsted_user, usr_iter->getAutoReply());
                        }
                    } else { // rqsted user already on channel
                        Service::errMsg(443, user, rqsted_user, rqsted_chnl_name);
                    }
                } else { // current user not on rqsted channel
                    Service::errMsg(442, user, rqsted_chnl_name);
                }
            } else { // rqsted user does not exist
                Service::errMsg(401, user, args[1]);
            }
        } else { //rqsted channel does not exist
            return ;
        }
    } else { // not enough params
        Service::errMsg(461, user, args[0]);
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

//void CommandList::pass(vector<std::string> args, User &user, list<User>& userList, string pass) {
//	if (user.isRegistered()) {
//		Service::errMsg(462, user);
//		return;
//	} else if (user.getRegisterPhase() == 2) {
//		close(user.getSocketFd());
//		userList.remove(user);
//		return;
//	}
//	cout << pass << endl;
//	if (args[1] == pass) {
//		cout << "valid" << endl;
//		user.setValidPass(true);
//		user.setRegisterPhase(user.getRegisterPhase() + 1);
//	}
//}

void CommandList::ison(std::vector<std::string> args, User& user, std::list<User> userList) {

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

//void CommandList::user(std::vector<std::string> args, User &user) {
//	if (args.size() < 4) {
//		Service::errMsg(461, user);
//		return;
//	}
//	user.setUsername(args[1]);
//	user.setHost(args[2]);
//	user.setServername(args[3]);
//	user.setRealname(args[4]);
//	user.setRegisterPhase(user.getRegisterPhase() + 1);
//	if (user.getRegisterPhase() == 3 && user.isValidPass()) motd(user);
//}

//  JOIN #foo,#bar fubar,foobar
void CommandList::join(vector<string> args, User &user, list<Channel> &channel_list) {

    vector<string> input_channels;
    vector<string> input_passwords;
    list<Channel>::iterator chnl_iter = channel_list.begin();

    if (args.size() > 1) {
        input_channels = Service::split(args[1], ',');
        if (args.size() == 3) {
            input_passwords = Service::split(args[2], ',');
        }
        for (size_t i = 0; i < input_channels.size(); ++i) {
            for (; chnl_iter != channel_list.end() && chnl_iter->_channel_name != input_channels[i]; ++chnl_iter) {}
            if (chnl_iter == channel_list.end()) {
                if (input_passwords[i].length() > 0) {
                    channel_list.push_back(Channel(args[1], user, input_passwords[i]));
                } else {
                    channel_list.push_back(Channel(args[1], user));
                }
                chnl_iter->_operator_list.push_back(user);
            } else {
                if (!chnl_iter->_is_invite_only) {
                    if (input_passwords[i].length() > 0) {
                        chnl_iter->addUser(user, input_passwords[i]);
                    } else {
                        chnl_iter->addUser(user);
                    }
                } else {
                    Service::errMsg(473, user, chnl_iter->_channel_name);
                }
            }
        }
    }
}

void CommandList::part(std::vector<std::string> args, User &user, list<Channel> &channel_list) {

	list<Channel>::iterator ch = channel_list.begin();
	bool	channelFound = false;
	bool	userFoundOnChannel = false;
	std::vector<std::string> channelVector;

	// #kek,#lal
	if (args.size() > 1) {
		channelVector = Service::split(args[1], ',');
		int channelVectorSize = channelVector.size();
		if (channelVector.size() > 0) {
			for (int i = 0; i < channelVectorSize; i++) {
				std::list<Channel>::iterator channelIter; // Check channels
				for (channelIter = channel_list.begin(); channelIter != channel_list.end(); ++channelIter) {
					if (channelIter->_channel_name == channelVector[i]) {
						channelFound = true;
						for (std::list<User>::iterator userlistIter = channelIter->_user_list.begin(); userlistIter != channelIter->_user_list.end(); ++userlistIter) {
							if (user.getNickname() == userlistIter->getNickname()) {
								userFoundOnChannel = true;
								// delete user from channel
								break;
							}
						}
					}
				}
				if (!channelFound) {
					Service::errMsg(403, user, channelIter->_channel_name);
				} else if (!userFoundOnChannel) {
					Service::errMsg(442, user, channelIter->_channel_name);
				}
				channelFound = false;
				userFoundOnChannel = false;
			}
		} else {
			// send error not enough arguments
		}
	}
}
