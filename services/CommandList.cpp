
#include "CommandList.hpp"

void CommandList::adminCmd(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == config["server.name"])) {
		Service::replyMsg(256, user, " " + config["server.name"]);
		Service::replyMsg(257, user, config["server.author.nickname"]);
		Service::replyMsg(258, user, config["server.author.name"]);
		Service::replyMsg(259, user, config["server.author.mail"]);
	} else
		Service::errMsg(402, user, args[1]);
}

void CommandList::awayCmd(std::vector<std::string> args, User &user) {
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

void CommandList::infoCmd(std::vector<std::string> args, User& user) {
	if (args.size() == 1 || (args.size() != 1 && args[1] == config["server.name"])) {
		Service::replyMsg(371, user, ">| Server Information |<");
		Service::replyMsg(371, user, "Compilation Time " + config["server.compilationTime"]);
		Service::replyMsg(371, user, "Server Version " + config["server.version"] + "." + config["server.debugLevel"]);
		Service::replyMsg(374, user);
	} else
		Service::errMsg(402, user, args[1]);
}

void CommandList::inviteCmd(std::vector<std::string> args, User &user) {

	string                  msg;
	string                  rqsted_user;
	string                  rqsted_chnl_name;
	list<User>::iterator    usr_iter = Server::userList.begin();
	list<Channel>::iterator chnl_iter = Server::channelList.begin();
	list<User>::iterator    chnl_usr_list = chnl_iter->_userList.begin();
	list<User>::iterator    chnl_oper_list = chnl_iter->_operator_list.begin();

	if (args.size() > 2) {
		rqsted_user = args[1];
		rqsted_chnl_name = args[2];
		for (; chnl_iter != Server::channelList.end() && chnl_iter->_channel_name != rqsted_chnl_name; ++chnl_iter) {} // searching rqsted channel
		if (chnl_iter != Server::channelList.end()) { // if rqsted channel exists
			for (; usr_iter != Server::userList.end() && usr_iter->getNickname() != rqsted_user; ++usr_iter) {} // searching rqsted user
			if (usr_iter != Server::userList.end()) { // if rqsted user exists
				for (; chnl_usr_list != chnl_iter->_userList.end()
				&& chnl_usr_list->getNickname() != user.getNickname(); ++chnl_usr_list) {} // searching current user on rqsted channel
				if (chnl_usr_list != chnl_iter->_userList.end()) { // if current user on rqsted channel
					chnl_usr_list = chnl_iter->_userList.begin();
					for (; chnl_usr_list != chnl_iter->_userList.end()
					&& chnl_usr_list->getNickname() != rqsted_user; ++chnl_usr_list) {} // searching rqsted user on rqsted channel
					if (chnl_usr_list == chnl_iter->_userList.end()) { // if rqsted user NOT on rqsted channel
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

void CommandList::isonCmd(std::vector<std::string> args, User& user) {

	std::string onlineUsers = "";

	if (args.size() == 1)
		Service::errMsg(461, user);
	else {
		for (std::list<User>::iterator userIt = Server::userList.begin(); userIt != Server::userList.end(); userIt++) {
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

//  JOIN #foo,#bar fubar,foobar
void CommandList::joinCmd(vector<string> args, User &user) {

	bool                                res;
	Channel                             new_chnl;
	vector<string>                      input_channels;
	vector<string>                      input_passwords;
	pair<list<Channel>::iterator, bool> chnl;

	if (args.size() > 1) {
		input_channels = Service::split(args[1], ',');
		if (args.size() == 3) {
			input_passwords = Service::split(args[2], ',');
		}
		for (size_t i = 0; i < input_channels.size(); ++i) {
			chnl = Service::isChannelExist(input_channels[i]); // searching new chnl among the existing
			if (!chnl.second) { // if rqsted chnl does not exist
				if (input_passwords.size() > i && input_passwords[i].length() > 0) {
					new_chnl = Channel(input_channels[i], user, input_passwords[i]);
				} else {
					new_chnl = Channel(input_channels[i], user);
				}
				new_chnl.addOperator(user);
				Server::channelList.push_back(new_chnl);
				user.joinedChannels.push_back(new_chnl);
				Service::replyMsg(332, user, new_chnl.getChannelName(), new_chnl.getChannelTopic());
			} else { // if rqsted chnl exist
				if (!chnl.first->_invite_only) {
					if (!input_passwords.empty() && input_passwords[i].length() > 0) { // with password
						res = chnl.first->addUser(user, input_passwords[i]);
					} else { // without password
						res = chnl.first->addUser(user);
					}
					if (res) { // if addUser is succesfull
						Service::replyMsg(332, user, chnl.first->getChannelName(), chnl.first->getChannelTopic());
					}
				} else { // rqsted chnl is invite only
					Service::errMsg(473, user, chnl.first->_channel_name);
				}
			}
		}
	} else { // not enough params
		Service::errMsg(461, user, args[0]);
	}
}

void CommandList::kickCmd(vector<string> args, User &user) {

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
			for (channelIter = Server::channelList.begin(); channelIter != Server::channelList.end(); ++channelIter) {
				if (channelIter->_channel_name == channelVector[i]) {
					channelFound = true;
					for (std::list<User>::iterator operlistIter = channelIter->_operator_list.begin(); !userIsOperator && operlistIter != channelIter->_operator_list.end(); ++operlistIter) {
						if (operlistIter->getNickname() == user.getNickname())
							userIsOperator = true;{}
					}
					for (std::list<User>::iterator userlistIter = channelIter->_userList.begin(); userIsOperator && userlistIter != channelIter->_userList.end(); ++userlistIter) {
						if (userVector[i] == userlistIter->getNickname()) {
							userFoundOnChannel = true;
							// delete user from channel
							Service::replyMsg(258, user, "USER FOUND AND KICKED FROM CHANNEL " + channelIter->_channel_name);
							Service::deleteChannelFromUser(*userlistIter, *channelIter);
							channelIter->deleteUser(*userlistIter);
							Server::channelList.remove_if(Service::channelIsEmpty);
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

void CommandList::killCmd(vector<string> args, User &user) {
	if (args.size() < 3) {
		Service::errMsg(461, user, args[0]);
	}
	else if (!user.isOper())
		Service::errMsg(481, user);
	else {
		for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); ++it) {
			if (it->getNickname() == args[1]) {
				Server::writing(it->getSocketFd(), args[2] + "\n");
				Server::kickUser(*it);
				return;
			}
		}
		Service::errMsg(401, user, args[1]);
	}
}

void CommandList::listCmd(vector<string> args, User &user) {

	std::vector<std::string> channelVector;

	if (args.size() == 1) {
		Service::replyMsg(321, user);
		for (list<Channel>::iterator ch = Server::channelList.begin(); ch != Server::channelList.end(); ch++) {
			if (!ch->_secret) {
				if (!ch->_private)
					Service::replyMsg(322, user, ch->getChannelName(), to_string(ch->_userList.size()), ch->getChannelTopic());
				else
					Service::replyMsg(322, user, "PRV");
			}
		}
		Service::replyMsg(323, user);
	} else if (args.size() > 1) {
		if (args.size() == 3 && args[2] != config["server.name"]) {
			Service::errMsg(402, user, args[2]);
		} else {
			Service::replyMsg(321, user);
			channelVector = Service::split(args[1], ',');

			std::list<Channel>::iterator channelIter; // Check channels
			std::vector<std::string>::iterator chVectorIter; // Check channels
			for (chVectorIter = channelVector.begin(); chVectorIter != channelVector.end(); chVectorIter++) {
				// cout << *chVectorIter << endl;
				for (channelIter = Server::channelList.begin(); channelIter != Server::channelList.end(); ++channelIter) {
					if (*chVectorIter == channelIter->getChannelName()) {
						if (!channelIter->_secret)
							Service::replyMsg(322, user, channelIter->getChannelName(), to_string(channelIter->_userList.size()), channelIter->getChannelTopic());
						break;
					}
				}
			}
			Service::replyMsg(323, user);
		}
	}
}

//void CommandList::modeCmd(vector<string> args, User &user) {
//
//    pair<list<Channel>::iterator, bool> rqsted_chnl;
//    pair<list<User>::iterator, bool> rqsted_user;
//    list<Channel>::iterator chnl_iter = Server::channelList.begin();
//    list<User>::iterator    chnl_oper_iter = chnl_iter->getOperListBegin();
//    list<User>::iterator    user_iter = Server::userList.begin();
//
//    if (checkModeParams(args, user)) {
//
//        if (args[1][0] == '#' || args[1][0] == '&') {
//            rqsted_chnl = Service::isChannelExist(args[1]);
//            if (rqsted_chnl.second) { // if channel exist
//                for (size_t i = 1; i < args[2].length(); ++i) {
//                    switch (args[2][i]) {
//                        case 'o': {
//                            rqsted_user = Service::isUserExist(args[3]);
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

void CommandList::namesCmd(vector<string> args, User &user) {

	std::vector<std::string> channelVector;

	if (args.size() == 1) {
		for (list<Channel>::iterator ch = Server::channelList.begin(); ch != Server::channelList.end(); ch++) {
			if (ch->_private || ch->_secret) {
				if (Service::isChannelExist(user.joinedChannels, ch->getChannelName()).second) { // if user is in channel
					string userlist = Service::getUsersFromList(user, ch->_userList);
					Service::replyMsg(353, user, ch->getChannelName(), userlist);
				}
			} else {
				string userlist = Service::getUsersFromList(user, ch->_userList);
				Service::replyMsg(353, user, ch->getChannelName(), userlist);
			}
		}
		std::string aloneUsers = "";
		for (list<User>::iterator usIter = Server::userList.begin(); usIter != Server::userList.end(); usIter++) {
			cout << "Empty: " << usIter->joinedChannels.empty() << endl;
			for (list<Channel>::iterator fuck = usIter->joinedChannels.begin(); fuck != usIter->joinedChannels.end(); fuck++) {
				cout << fuck->getChannelName() << endl;
			}
			if (usIter->joinedChannels.empty() && !usIter->isInvisible())
				aloneUsers += usIter->getNickname() + " ";
			else if (usIter->joinedChannels.empty() && usIter->isInvisible() && usIter->getNickname() == user.getNickname())
				aloneUsers += usIter->getNickname() + " ";
		}
		Service::replyMsg(353, user, "* *", aloneUsers);
		Service::replyMsg(366, user, "*");
		/*listAllChannels*/
	} else {
		channelVector = Service::split(args[1], ',');
		std::list<Channel>::iterator channelIter; // Check channels
		std::vector<std::string>::iterator chVectorIter; // Check channels
		for (size_t i = 0; i < channelVector.size(); i++) {
			pair<list<Channel>::iterator, bool> kex = Service::isChannelExist(channelVector[i]);
			if (kex.second) {
				if (kex.first->_private || kex.first->_secret) {
					if (Service::isChannelExist(user.joinedChannels, kex.first->getChannelName()).second) { // if user is in channel
						string userlist = Service::getUsersFromList(user, kex.first->_userList);
						Service::replyMsg(353, user, kex.first->getChannelName(), userlist);
					}
				} else {
					string userlist = Service::getUsersFromList(user, kex.first->_userList);
					Service::replyMsg(353, user, kex.first->getChannelName(), userlist);
				}
				Service::replyMsg(366, user, kex.first->getChannelName());
			}
		}
	}
}

int CommandList::nickCmd(std::vector<std::string> args, User& user) {
	if (args.size() == 1) {
		Service::errMsg(461, user);
		return 0;
	}
	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); ++it) {
		if (it->getNickname() == args[1]) {
			Service::errMsg(433, user, args[1]);
			return 0;
		}
	}
	user.setNickname(args[1]);
//	user.setRegisterPhase(user.getRegisterPhase() + 1);
//	if (user.getRegisterPhase() == 3 && user.isValidPass()) { motd(user); return 7; }
	user.setValidPass(true);
	user.setRegisterPhase(3);
	motd(user);
	return 7;
//	return 0;

}

void CommandList::noticeCmd(vector<string> args, User &user) {
	privmsgCmd(args, user, true);
}

void CommandList::operCmd(vector<string> args, User& user) {
	if (args.size() < 3)
		Service::errMsg(461, user, args[0]);
	else if (config["operators." + args[1]] != sha256(args[2])) {
		Service::errMsg(464, user);
	} else {
		user.setOper(true);
		Service::replyMsg(381, user);
	}
}

void CommandList::partCmd(std::vector<std::string> args, User &user) {

	list<Channel>::iterator ch = Server::channelList.begin();
	bool	channelFound = false;
	bool	userFoundOnChannel = false;
	std::vector<std::string> channelVector;

	if (args.size() > 1) {
		channelVector = Service::split(args[1], ',');
		int channelVectorSize = channelVector.size();
		if (channelVector.size() > 0) {
			for (int i = 0; i < channelVectorSize; i++) {
				std::list<Channel>::iterator channelIter; // Check channels
				for (channelIter = Server::channelList.begin(); channelIter != Server::channelList.end(); ++channelIter) {
					if (channelIter->_channel_name == channelVector[i]) {
						channelFound = true;
						for (std::list<User>::iterator userlistIter = channelIter->_userList.begin(); userlistIter != channelIter->_userList.end(); ++userlistIter) {
							if (user.getNickname() == userlistIter->getNickname()) {
								userFoundOnChannel = true;
								// delete user from channel
								Service::replyMsg(258, user, "USER FOUND AND DELETED FROM CHANNEL " + channelIter->_channel_name);
								Service::deleteChannelFromUser(user, *channelIter);
								channelIter->deleteUser(*userlistIter);
								Server::channelList.remove_if(Service::channelIsEmpty);
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

//void CommandList::passCmd(vector<string> args, User &user, string pass) {
//	if (user.isRegistered()) {
//		Service::errMsg(462, user);
//		return;
//	} else if (user.getRegisterPhase() == 2) {
//		kickUser(user);
//		return;
//	}
//	if (args[1] == pass) {
//		user.setValidPass(true);
//		user.setRegisterPhase(user.getRegisterPhase() + 1);
//	}
//}

int CommandList::pingCmd(vector<string> args, User &user) {
	return (args.size() == 1) ? Service::errMsg(409, user), 0
	: Server::writing(user.getSocketFd(), ":" + config["server.name"] + " PONG :" + args[1] + "\n"), 8;
}

int CommandList::pongCmd(vector<string> args, User &user) {
	return (args[1] == config["server.name"]) ? 8
	: (Service::errMsg(402, user, args[1]), 0);
}

void CommandList::privmsgCmd(vector<string> args, User &user, bool isNotice) {
	if (args.size() == 1)
		Service::errMsg(411, user, args[0]);
	else if (args.size() == 2)
		Service::errMsg(412, user);
	else {
		vector<string> arg_list = Service::split(args[1], ',');
		for (vector<string>::iterator it = arg_list.begin(); it != arg_list.end(); ++it) {
			if (it->front() == '#' || it->front() == '&') {
				pair<list<Channel>::iterator, bool> pair = Service::isChannelExist(*it);
				if (pair.second) {
					if (pair.first->_no_outside || !pair.first->inChannel(user))
						Service::errMsg(404, user, pair.first->getChannelName());
					else {
						for (list<User>::iterator ch_user = pair.first->_userList.begin(); ch_user != pair.first->_userList.end(); ++ch_user) {
							Service::sendMsg(1, user, *ch_user, args[0], pair.first->getChannelName(), args[2]);
						}
					}
				} else
					Service::errMsg(401, user, *it);
			}
			pair<list<User>::iterator, bool> pair = Service::isUserExist(*it);
			if (pair.second) {
				Service::sendMsg(1, user, *(pair.first), args[0], pair.first->getNickname(), args[2]);
				if (pair.first->isAway() && !isNotice)
					Service::replyMsg(301, user, pair.first->getNickname(), pair.first->getAutoReply());
			}
		}
	}
}

int CommandList::restartCmd(User &user) {
	if (!user.isOper()) {
		Service::errMsg(481, user);
		return -1;
	}
	return 3;
}

void CommandList::rehashCmd(User &user) {
	if (!user.isOper())
		Service::errMsg(481, user);
	else {
		config.reload();
		Service::replyMsg(382, user);
	}
}

void CommandList::timeCmd(vector<string> args, User &user) {
	(args.size() > 1 && args[1] != config["server.name"])
	? Service::errMsg(402, user, args[1])
	: Service::replyMsg(391, user, config["server.name"], Service::getDate());
}

//int CommandList::user(vector<std::string> args, User &user) {
//	if (args.size() < 4) {
//		Service::errMsg(461, user);
//		return 0;
//	}
//	user.setUsername(args[1]);
//	user.setHost(args[2]);
//	user.setServername(args[3]);
//	user.setRealName(args[4]);
//	user.setRegisterPhase(user.getRegisterPhase() + 1);
//	if (user.getRegisterPhase() == 3 && user.isValidPass()) { motd(user); return 7; }
//	return 0;
//}

void CommandList::versionCmd(std::vector<std::string> args, User &user) {
	(args.size() > 1 && args[1] != config["server.name"])
	? Service::errMsg(402, user, args[1])
	: Service::replyMsg(351, user, config["server.version"], config["server.debugLevel"], config["server.name"], config["server.release"]);
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

