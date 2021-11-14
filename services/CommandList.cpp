
#include "CommandList.hpp"

void CommandList::admin(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == config["server.name"])) {
		Service::replyMsg(256, user, " " + config["server.name"]);
		Service::replyMsg(257, user, config["server.author.nickname"]);
		Service::replyMsg(258, user, config["server.author.name"]);
		Service::replyMsg(259, user, config["server.author.mail"]);
	} else
		Service::errMsg(402, user, args[1]);
}

void CommandList::motd(User &user) {
	std::ifstream infile("resources/daily");
	if (infile) {
		std::string dailyMessageLine;
		Service::replyMsg(375, user, config["server.name"]);
		while (std::getline(infile, dailyMessageLine))
			Service::replyMsg(372, user, dailyMessageLine);
		Service::replyMsg(376, user);
	} else
		Service::errMsg(422, user);
}

void CommandList::nick(std::vector<std::string> args, User& user, list<User>& userList) {
	if (args.size() == 1) {
		Service::errMsg(461, user);
		return;
	}
	for (list<User>::iterator it = userList.begin(); it != userList.end(); ++it) {
		if (it->getNickname() == args[1]) {
			Service::errMsg(433, user, args[1]);
			return;
		}
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

    string                  msg;
    string                  rqsted_user;
    string                  rqsted_chnl_name;
    list<User>::iterator    usr_iter = user_list.begin();
    list<Channel>::iterator chnl_iter = channel_list.begin();
    list<User>::iterator    chnl_usr_list = chnl_iter->_user_list.begin();
    list<User>::iterator    chnl_oper_list = chnl_iter->_operator_list.begin();

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
                        if (chnl_iter->_invite_only) { // if rqsted channel is invite only
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
	if (args.size() == 1 || (args.size() != 1 && args[1] == config["server.name"])) {
		Service::replyMsg(371, user, ">| Server Information |<");
		Service::replyMsg(371, user, "Compilation Time " + config["server.compilationTime"]);
		Service::replyMsg(371, user, "Server Version " + config["server.version"] + "." + config["server.debugLevel"]);
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
//	if (args[1] == pass) {
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
//	user.setRealName(args[4]);
//	user.setRegisterPhase(user.getRegisterPhase() + 1);
//	if (user.getRegisterPhase() == 3 && user.isValidPass()) motd(user);
//}

//  JOIN #foo,#bar fubar,foobar
void CommandList::join(vector<string> args, User &user, list<Channel> &channel_list) {

    bool                    res;
    Channel                 new_chnl;
    vector<string>          input_channels;
    vector<string>          input_passwords;
    list<Channel>::iterator chnl_iter = channel_list.begin();

    if (args.size() > 1) {
        input_channels = Service::split(args[1], ',');
        if (args.size() == 3) {
            input_passwords = Service::split(args[2], ',');
        }
        for (size_t i = 0; i < input_channels.size(); ++i) {
            for (; chnl_iter != channel_list.end() && chnl_iter->_channel_name != input_channels[i]; ++chnl_iter) {} // searching new chnl among the existing
            if (chnl_iter == channel_list.end()) { // if does not exist
                if (input_passwords.size() > i && input_passwords[i].length() > 0) {
                    new_chnl = Channel(args[1], user, input_passwords[i]);
                } else {
                    new_chnl = Channel(args[1], user);
                }
                new_chnl.addOperator(user);
                channel_list.push_back(new_chnl);
                Service::replyMsg(332, user, new_chnl.getChannelName(), new_chnl.getChannelTopic());
            } else { // if exist
                if (!chnl_iter->_invite_only) {
                    if (input_passwords[i].length() > 0) {
                        res = chnl_iter->addUser(user, input_passwords[i]);
                    } else {
                        res = chnl_iter->addUser(user);
                    }
                    if (res) {
                        Service::replyMsg(332, user, chnl_iter->getChannelName(), chnl_iter->getChannelTopic());
                    }
                } else {
                    Service::errMsg(473, user, chnl_iter->_channel_name);
                }
            }
        }
    } else { // not enough params
        Service::errMsg(461, user, args[0]);
    }
}

void CommandList::part(std::vector<std::string> args, User &user, list<Channel> &channel_list) {

	list<Channel>::iterator ch = channel_list.begin();
	bool	channelFound = false;
	bool	userFoundOnChannel = false;
	std::vector<std::string> channelVector;

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
								Service::replyMsg(258, user, "USER FOUND AND DELETED FROM CHANNEL " + channelIter->_channel_name);
								channelIter->deleteUser(*userlistIter);
								Service::emptyChannel(channel_list);
								break ;
							}
						}
						if (userFoundOnChannel)
							break ;
					}
				}
				if (!channelFound) {
					Service::errMsg(403, user, args[1]);
				} else if (!userFoundOnChannel) {
					Service::errMsg(442, user, args[1]);
				}
				channelFound = false;
				userFoundOnChannel = false;
			}
		}
	} else {
		Service::errMsg(461, user, "PART");
	}
}

void CommandList::time(vector<string> args, User &user) {
	(args.size() > 1 && args[1] != config["server.name"])
		? Service::errMsg(402, user, args[1])
		: Service::replyMsg(391, user, config["server.name"], Service::getDate());
}

void CommandList::version(std::vector<std::string> args, User &user) {
	(args.size() > 1 && args[1] != config["server.name"])
	? Service::errMsg(402, user, args[1])
	: Service::replyMsg(351, user, config["server.version"], config["server.debugLevel"], config["server.name"], config["server.release"]);
}

int CommandList::restart(User &user) {
	if (!user.isOper()) {
		Service::errMsg(481, user);
		return -1;
	}
	return 3;
}

void CommandList::kick(vector<string> args, User &user, list<Channel> &channel_list) {

 	std::vector<std::string> channelVector;
 	std::vector<std::string> userVector;
 	bool	channelFound = false;
 	bool	userFoundOnChannel = false;
 	bool	userIsOperator = false;


 	if (args.size() > 2) {
 		channelVector = Service::split(args[1], ',');
 		userVector = Service::split(args[2], ',');
 		int channelVectorSize = channelVector.size();
 		if (channelVectorSize != userVector.size())
 		{
 			Service::errMsg(461, user, "PART");
 			return ;
 		}
 		for (int i = 0; i < channelVectorSize; i++) {
 			std::list<Channel>::iterator channelIter; // Check channels
 			for (channelIter = channel_list.begin(); channelIter != channel_list.end(); ++channelIter) {
 				if (channelIter->_channel_name == channelVector[i]) {
 					channelFound = true;
 					for (std::list<User>::iterator operlistIter = channelIter->_operator_list.begin(); !userIsOperator && operlistIter != channelIter->_operator_list.end(); ++operlistIter) {
 						if (operlistIter->getNickname() == user.getNickname())
 							userIsOperator = true;
 					}
 					for (std::list<User>::iterator userlistIter = channelIter->_user_list.begin(); userIsOperator && userlistIter != channelIter->_user_list.end(); ++userlistIter) {
 						if (userVector[i] == userlistIter->getNickname()) {
 							userFoundOnChannel = true;
 							// delete user from channel
 							Service::replyMsg(258, user, "USER FOUND AND KICKED FROM CHANNEL " + channelIter->_channel_name);
 							channelIter->deleteUser(*userlistIter);
 							Service::emptyChannel(channel_list);
 							userIsOperator = false;
 							break ;
 						}
 					}
 					if (userFoundOnChannel)
 						break ;
 				}
 			}
 			if (!channelFound) {
 				Service::errMsg(403, user, args[1]);
 			} else if (!userIsOperator) {
 				Service::errMsg(482, user, channelIter->_channel_name);
 			}
 			else if (!userFoundOnChannel) {
 				Service::errMsg(442, user, args[1]);
 			}
 			channelFound = false;
 			userFoundOnChannel = false;
 			userIsOperator = false;
 		}
 	} else {
 		Service::errMsg(461, user, "KICK");
 	}
 }

 //todo нестабильно работает, протестировать
void CommandList::kill(vector<string> args, User &user, list<User> &user_list) {
	if (args.size() < 3) {
		Service::errMsg(461, user, args[0]);
	}
	else if (!user.isOper())
		Service::errMsg(481, user);
	else {
		for (list<User>::iterator it = user_list.begin(); it != user_list.end(); ++it) {
			if (it->getNickname() == args[1]) {
				Server::writing(it->getSocketFd(), args[2] + "\n");
				close(it->getSocketFd());
				user_list.erase(it);
				return;
			}
		}
		Service::errMsg(401, user, args[1]);
	}
}

void CommandList::oper(vector<string> args, User& user) {
	if (args.size() < 3)
		Service::errMsg(461, user, args[0]);
	else if (config["operators." + args[1]] != sha256(args[2])) {
		Service::errMsg(464, user);
	} else {
		user.setOper(true);
		Service::replyMsg(381, user);
	}
}


//bool CommandList::checkModeFlags(string flags_str, string flags_variables, User &user, int &params_num) {
//
//    string          chnl_flags = "opsitnmlbvk";
//    string          user_flags = "iswo";
//    vector<int>     flags_cnt[255];
//
//    for (size_t i = 1; i < flags_str.length(); ++i) {
//        if (flags_variables.find(flags_str[i]) != string::npos) {
//            flags_cnt[flags_str[i]][0]++;
//            if (flags_cnt[flags_str[i]][0] > 1) { // if flags occurs more than once
//                Service::errMsg(501, user, "MODE");
//                return false;
//            }
//        } else {
//            Service::errMsg(472, user, string("" + flags_str[i]));
//            return false;
//        }
//}

//bool CommandList::checkModeParams(vector<string> args, User &user) {
//
//    int             chnl_params_num = 0;
//    bool            special_flags = false;
//    string          chnl_flags = "opsitnmlbvk";
//    string          user_flags = "iswo";
//    vector<int>     flags[255];
//
//
//    if (args.size() > 2) { // if cmd_name + chnl_name/user_name + flags exist
//        if (args[2][0] == '+' || args[2][0] == '-') { // if it begins with +/- exist
//            if (args[1][0] == '#' || args[1][0] == '&') { // if MODE for chnl
//                for (size_t i = 1; i < args[2].length(); ++i) { // checking flags
//                    if (chnl_flags.find(args[2][i]) != string::npos) {
//                        flags[args[2][i]][0]++;
//                        if (flags[args[2][i]][0] > 1) { // if flags occurs more than once
//                            Service::errMsg(501, user, args[0]);
//                            return false;
//                        }
//                    } else { // unknown flag
//                        Service::errMsg(472, user, string("" + args[2][i]));
//                        return false;
//                    }
//                    if (special_flags == true && args[2].length() > 2) { // if flags [o l b k] not single in line
//                        Service::errMsg(472, user, args[2]);
//                        return false;
//                    }
//                    if (args[2][i] == 'o' || args[2][i] == 'l' || args[2][i] == 'b' || args[2][i] == 'k') {
//                        special_flags = true;
//                    }
//                }
//                if (special_flags && args[3].empty()) { // number of expected params is invalid (for chnl MODE)
//                    Service::errMsg(461, user, args[0]);
//                    return false;
//                }
//            } else { // MODE for user
//                for (size_t i = 1; i < args[2].length(); ++i) { // checking flags
//                    if (user_flags.find(args[2][i]) != string::npos) {
//                        flags[args[2][i]][0]++;
//                        if (flags[args[2][i]][0] > 1) { // if flags occurs more than once
//                            Service::errMsg(501, user, args[0]);
//                            return false;
//                        }
//                    } else { // unknown flag
//                        Service::errMsg(472, user, string("" + args[2][i]));
//                        return false;
//                    }
//                }
//            }
//        } else { // unknown flag (no prefix +/-)
//            Service::errMsg(472, user, args[2]);
//            return false;
//        }
//    } else { // not enough params (for both MODE)
//        Service::errMsg(461, user, args[0]);
//        return false;
//    }
//    return true;
//}

//void CommandList::mode(vector<string> args, User &user, list<User> &user_list, list<Channel> &channel_list) {
//
//    pair<list<Channel>::iterator, bool> rqsted_chnl;
//    pair<list<User>::iterator, bool> rqsted_user;
//    list<Channel>::iterator chnl_iter = channel_list.begin();
//    list<User>::iterator    chnl_oper_iter = chnl_iter->getOperListBegin();
//    list<User>::iterator    user_iter = user_list.begin();
//
//    if (checkModeParams(args, user)) {
//
//        if (args[1][0] == '#' || args[1][0] == '&') {
//            rqsted_chnl = Service::isInList(channel_list.begin(), channel_list.end(), args[1]);
//            if (rqsted_chnl.second) { // if channel exist
//                for (size_t i = 1; i < args[2].length(); ++i) {
//                    switch (args[2][i]) {
//                        case 'o': {
//                            rqsted_user = Service::isInList(user_list.begin(), user_list.end(), args[3]);
//                            if (rqsted_user.second) { // if input user exist
//                                if (Service::isInList(rqsted_chnl.first->getOperListBegin(), rqsted_chnl.first->getOperListEnd(), user.getNickname()).second) { // if cuurent user operator on rqsted channel
//                                    if (Service::isInList(rqsted_chnl.first->getOperListBegin(), rqsted_chnl.first->getOperListEnd(), args[3]).second) { // if input user not operator yet on rqsted channel
//                                        if (args[2][0] == '+') {
//                                            Service::replyMsg(221,user, args[3] + "is already operator on " + args[1]);
//                                            return;
//                                        } else {
//                                            rqsted_chnl.first->deleteOperator(*rqsted_user.first);
//                                            Service::replyMsg(221,user, args[3] + "removed from operator list on " + args[1]);
//                                            return;
//                                        }
//                                    } else {
//                                        if (args[2][0] == '+') {
//                                            rqsted_chnl.first->addOperator(*rqsted_user.first);
//                                            Service::replyMsg(221,user, args[3] + "is now operator on " + args[1]);
//                                            return;
//                                        } else {
//                                            Service::replyMsg(221,user, args[3] + "is already not an operator on " + args[1]);
//                                            return;
//                                        }
//                                    }
//                                } else {
//                                    Service::errMsg(482, user, args[1]);
//                                }
//                            } else {
//                                Service::errMsg(401, user, args[3]);
//                            }
//                            break;
//                        }
//                    }
//                }
//            } else {
//                Service::errMsg(403, user, args[1]);
//            }
//        } else {
//
//        }
//    }
//}


