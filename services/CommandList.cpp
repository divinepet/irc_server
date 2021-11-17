
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
							Service::sendMsg(user, *usr_iter, args[0], usr_iter->getNickname(), rqsted_chnl_name);
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
				Service::sendMsg(user, user, args[0], new_chnl.getChannelName());
				Service::replyMsg(331, user, new_chnl.getChannelName(), new_chnl.getChannelTopic());
				Service::replyMsg(353, user, new_chnl.getChannelName(), "@" + user.getNickname());
				Service::replyMsg(366, user, new_chnl.getChannelName());
			} else { // if rqsted chnl exist
				if (!chnl.first->_invite_only) {
					if (!input_passwords.empty() && input_passwords[i].length() > 0) { // with password
						res = chnl.first->addUser(user, input_passwords[i]);
						user.joinedChannels.push_back(*chnl.first);
					} else { // without password
						res = chnl.first->addUser(user);
						user.joinedChannels.push_back(*chnl.first);
					}
					if (res) { // if addUser is succesfull
						for (list<User>::iterator usr_in_ch = chnl.first->getUserList().begin(); usr_in_ch != chnl.first->getUserList().end(); ++usr_in_ch)
							Service::sendMsg(user, *usr_in_ch, args[0], chnl.first->getChannelName());
						Service::sendMsg(user, user, args[0], chnl.first->getChannelName());
						Service::replyMsg(331, user, chnl.first->getChannelName(), chnl.first->getChannelTopic());
						Service::replyMsg(353, user, chnl.first->getChannelName(),Service::to_string(chnl.first->getOperList(), true)
																			+ Service::to_string(chnl.first->getUserList(), *(chnl.first)));
						Service::replyMsg(366, user, chnl.first->getChannelName());
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
							for (list<User>::iterator usr_in_ch = channelIter->getUserList().begin(); usr_in_ch != channelIter->getUserList().end(); ++usr_in_ch)
								Service::sendMsg(user, *usr_in_ch, args[0], channelIter->getChannelName(), args[3]);
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
				if (!ch->_private || Service::isUserExist(ch->_userList, user.getNickname()).second)
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

bool CommandList::checkModeParams(vector<string> args, User &user) {

    bool            special_flags = false;
    string          chnl_flags = "opsitnmlbvk";
    string          user_flags = "iswo";
    vector<int>     flags(255);


    if (args.size() > 2) { // if cmd_name + chnl_name/user_name + flags exist
        if (args[2][0] == '+' || args[2][0] == '-') { // if it begins with +/- exist
            if (args[1][0] == '#' || args[1][0] == '&') { // if MODE for chnl
                for (size_t i = 1; i < args[2].length(); ++i) { // checking flags
                    if (chnl_flags.find(args[2][i]) != string::npos) {
                        flags[args[2][i]]++;
                        if (flags[args[2][i]] > 1) { // if flags occurs more than once
                            Service::errMsg(501, user, args[0]);
                            return false;
                        }
                    } else { // unknown flag
                        Service::errMsg(472, user, to_string(args[2][i]));
                        return false;
                    }
                    if (special_flags == true && args[2].length() > 2) { // if flags [o l b k] not single in line
                        Service::errMsg(472, user, args[2]);
                        return false;
                    }
                    if (args[2][i] == 'o' || args[2][i] == 'l'
                        || args[2][i] == 'k' || args[2][i] == 't') {
                        special_flags = true;
                    }
                }
                if (special_flags && args[3].empty()) { // number of expected params is invalid (for chnl MODE)
                    Service::errMsg(461, user, args[0]);
                    return false;
                }
            } else { // MODE for user
                for (size_t i = 1; i < args[2].length(); ++i) { // checking flags
                    if (user_flags.find(args[2][i]) != string::npos) {
                        flags[args[2][i]]++;
                        if (flags[args[2][i]] > 1) { // if flags occurs more than once
                            Service::errMsg(501, user, args[0]);
                            return false;
                        }
                    } else { // unknown flag
                        Service::errMsg(472, user, to_string(args[2][i]));
                        return false;
                    }
                }
            }
        } else { // unknown flag (no prefix +/-)
            Service::errMsg(472, user, args[2]);
            return false;
        }
    } else { // not enough params (for both MODE)
        Service::errMsg(461, user, args[0]);
        return false;
    }
    return true;
}

void CommandList::setChnlModeOperator(vector<string> args, User &user, list<User> &user_list, Channel &rqsted_chnl) {

    pair<list<User>::iterator, bool>    rqsted_user;

    rqsted_user = Service::isUserExist(user_list, args[3]);
    if (rqsted_user.second) { // if input user exist
        if (Service::isUserExist(rqsted_chnl.getOperList(), args[3]).second) { // if input user not operator yet on rqsted channel
            if (args[2][0] == '+') {
                Service::replyMsg(221,user, args[3] + "is already operator on " + args[1]);
                return;
            } else {
                rqsted_chnl.deleteOperator(*rqsted_user.first);
                Service::replyMsg(221,user, args[3] + "removed from operator list on " + args[1]);
                return;
            }
        } else {
            if (args[2][0] == '+') {
                rqsted_chnl.addOperator(*rqsted_user.first);
                Service::replyMsg(221,user, args[3] + "is now operator on " + args[1]);
                return;
            } else {
                Service::replyMsg(221,user, args[3] + "is already not an operator on " + args[1]);
                return;
            }
        }
    } else { // NO such user
        Service::errMsg(401, user, args[3]);
    }
}

void CommandList::setChnlModePrivate(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setPrivateFlag(true);
        Service::replyMsg(221,user, "private mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "private mode on " + args[1] + " is disabled");
        rqsted_chnl.setPrivateFlag(false);
    }
}

void CommandList::setChnlModeSecret(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setSecretFlag(true);
        Service::replyMsg(221,user, "secret mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "secret mode on " + args[1] + " is disabled");
        rqsted_chnl.setSecretFlag(false);
    }
}

void CommandList::setChnlModeInvite(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setInviteFlag(true);
        Service::replyMsg(221,user, "invite_only mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "invite_only mode on " + args[1] + " is disabled");
        rqsted_chnl.setInviteFlag(false);
    }
}

void CommandList::setChnlModeTopic(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setTopicFlag(true);
        Service::replyMsg(221,user, "topic_settable_by_channel_operator mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "topic_settable_by_channel_operator mode on " + args[1] + " is disabled");
        rqsted_chnl.setTopicFlag(false);
    }
}

void CommandList::setChnlModeOutside(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setOutsideFlag(true);
        Service::replyMsg(221,user, "no_messages_to_channel_from_clients_on_the_outside mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "no_messages_to_channel_from_clients_on_the_outside mode on " + args[1] + " is disabled");
        rqsted_chnl.setOutsideFlag(false);
    }
}

void CommandList::setChnlModeModerated(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setModeratedFlag(true);
        Service::replyMsg(221,user, "no_messages_to_channel_from_clients_on_the_outside mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "no_messages_to_channel_from_clients_on_the_outside mode on " + args[1] + " is disabled");
        rqsted_chnl.setModeratedFlag(false);
    }
}

void CommandList::setChnlModeLimit(vector<string> args, User &user, Channel &rqsted_chnl) {

    unsigned int result;

    for (size_t i = 0; i < args[3].length(); ++i) {
        if (args[2][0] == '-' || args[3][0] == '0' || !isnumber(args[3][i])) {
            Service::errMsg(501, user, args[3]);
            return ;
        }
    }
    try {
        result = stoi(args[3]);
        Service::replyMsg(221,user, "user_limit mode on " + args[1] + " is now " + to_string(result));
        rqsted_chnl.setUserLimit(result);
    } catch (std::exception) {
        Service::errMsg(501, user, args[3]);
        return;
    }
}

void CommandList::setChnlModeBan(vector<string> args, User &user, Channel &rqsted_chnl) {

    list<string> ban_list = rqsted_chnl.getBanList();

    if (args[2][0] == '+') {
        if (args.size() < 4) { // single +b
            for (list<string>::iterator it = ban_list.begin(); it != ban_list.end(); ++it) {
                Service::replyMsg(367, user, rqsted_chnl.getChannelName() + *it);
            }
            Service::replyMsg(368, user, rqsted_chnl.getChannelName());

        } else { // +b with params
            ban_list.push_back(args[3]);
            Service::replyMsg(367, user, rqsted_chnl.getChannelName(), args[3], " has been added to ban list");
        }
    } else {
        if (args.size() > 3) { // -b with params
            ban_list.remove(args[3]);
            Service::replyMsg(367, user, rqsted_chnl.getChannelName(), args[3], " has been removed from ban list");
        } else { // -b without params
            Service::errMsg(461, user, args[0]);
            return ;
        }
    }

}

void CommandList::setChnlModeVoice(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (args[2][0] == '+') {
        rqsted_chnl.setVoiceFlag(true);
        Service::replyMsg(221,user, "the ability to speak on a moderated channel mode on " + args[1] + " is enabled");
    } else {
        Service::replyMsg(221,user, "the ability to speak on a moderated channel mode on " + args[1] + " is disabled");
        rqsted_chnl.setVoiceFlag(false);
    }
}

void CommandList::setChnlModeKey(vector<string> args, User &user, Channel &rqsted_chnl) {
    if (!rqsted_chnl.isPassword()) {
        rqsted_chnl.setPassword(args[3]);
        Service::replyMsg(324, user, rqsted_chnl.getChannelName(), "KEY", args[3]);
    } else {
        Service::errMsg(467, user, rqsted_chnl.getChannelName());
    }
}

void CommandList::setUserModeInvisible(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        user.setInvisible(true);
        Service::replyMsg(221, user, "invisible mode is enabled");
    } else {
        user.setInvisible(false);
        Service::replyMsg(221, user, "invisible mode is disabled");
    }
}

void CommandList::setUserModeNoticed(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        user.setNoticed(true);
        Service::replyMsg(221, user, "reception_notices_from_server mode is enabled");
    } else {
        user.setNoticed(false);
        Service::replyMsg(221, user, "reception_notices_from_server mode is disabled");
    }
}

void CommandList::setUserModeWallops(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        user.setWallops(true);
        Service::replyMsg(221, user, "reception_wallops mode is enabled");
    } else {
        user.setWallops(false);
        Service::replyMsg(221, user, "reception_wallops mode is disabled");
    }
}

void CommandList::setUserModeOperator(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        Service::errMsg(472, user, "+o");
    } else {
        user.setOper(false);
        Service::replyMsg(221, user, "operator mode is disabled");
    }
}

void CommandList::setChnlMode(vector<string> args, User &user, list<User> &user_list, Channel &chnl) {
    for (size_t i = 1; i < args[2].length(); ++i) {
        switch (args[2][i]) {
            case 'o': {
                setChnlModeOperator(args, user, user_list, chnl);
                break;
            }
            case 'p': {
                setChnlModePrivate(args, user, chnl);
                break;
            }
            case 's': {
                setChnlModeSecret(args, user, chnl);
                break;
            }
            case 'i': {
                setChnlModeInvite(args, user, chnl);
                break;
            }
            case 't': {
                setChnlModeTopic(args, user, chnl);
                break;
            }
            case 'n': {
                setChnlModeOutside(args, user, chnl);
                break;
            }
            case 'm': {
                setChnlModeModerated(args, user, chnl);
                break;
            }
            case 'l': {
                setChnlModeLimit(args, user, chnl);
                break;
            }
            case 'b': {
                setChnlModeBan(args, user, chnl);
                break;
            }
            case 'v': {
                setChnlModeVoice(args, user, chnl);
                break;
            }
            case 'k': {
                setChnlModeKey(args, user, chnl);
                break;
            }
        }
    }
}

void CommandList::setUserMode(vector<string> args, User &user) {
    for (size_t i = 1; i < args[2].length(); ++i) {
        switch (args[2][i]) {
            case 'i': {
                setUserModeInvisible(args, user);
                break;
            }
            case 's': {
                setUserModeNoticed(args, user);
                break;
            }
            case 'w': {
                setUserModeWallops(args, user);
                break;
            }
            case 'o': {
                setUserModeOperator(args, user);
                break;
            }
        }
    }
}

void CommandList::mode(vector<string> args, User &user) {

    pair<list<User>::iterator, bool>    rqsted_user;
    pair<list<Channel>::iterator, bool> rqsted_chnl;

    if (checkModeParams(args, user)) {
        if (args[1][0] == '#' || args[1][0] == '&') { // if MODE fot channel
            rqsted_chnl = Service::isChannelExist(Server::channelList, args[1]);
            if (rqsted_chnl.second) { // if rqsted channel exist
                if (Service::isUserExist(rqsted_chnl.first->getOperList(), user.getNickname()).second) { // if cuurent user operator on rqsted channel
                    setChnlMode(args, user, Server::userList, *rqsted_chnl.first);
                } else { // user NOT operator on rqsted channel
                    Service::errMsg(482, user, args[1]);
                }
            } else {
                Service::errMsg(403, user, args[1]);
            }
        } else { // if MODE for user
            if (user.getNickname() == args[1]) { // current user name is same as rqsted nickname
                setUserMode(args, user);
            } else { // user name and input nickname not matched
                Service::errMsg(502, user);
            }
        }
    }
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

void	CommandList::namesCmd(vector<string> args, User &user) {

	std::vector<std::string> channelVector;

	if (args.size() == 1) {
		for (list<Channel>::iterator ch = Server::channelList.begin(); ch != Server::channelList.end(); ch++) {
			if (ch->_private || ch->_secret) {
				if (Service::isChannelExist(user.joinedChannels, ch->getChannelName()).second) { // if user is in channel
					string userlist = Service::getUsersFromList(user, ch->_userList, *ch);
					Service::replyMsg(353, user, ch->getChannelName(), userlist);
				}
			} else {
				string userlist = Service::getUsersFromList(user, ch->_userList, *ch);
				Service::replyMsg(353, user, ch->getChannelName(), userlist);
			}
		}
		std::string aloneUsers = "";
		for (list<User>::iterator usIter = Server::userList.begin(); usIter != Server::userList.end(); usIter++) {
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
			pair<list<Channel>::iterator, bool> kex = Service::isChannelExist(Server::channelList, channelVector[i]);
			if (kex.second) {
				if (kex.first->_private || kex.first->_secret) {
					if (Service::isChannelExist(user.joinedChannels, kex.first->getChannelName()).second) { // if user is in channel
						string userlist = Service::getUsersFromList(user, kex.first->_userList, *kex.first);
						Service::replyMsg(353, user, kex.first->getChannelName(), userlist);
					}
				} else {
					string userlist = Service::getUsersFromList(user, kex.first->_userList, *kex.first);
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
	if (args.size() < 2)
		Service::errMsg(461, user, "PART");
	else {
		channelVector = Service::split(args[1], ',');

		for (size_t i = 0; i < channelVector.size(); i++) {
			std::list<Channel>::iterator channelIter; // Check channels
			for (channelIter = Server::channelList.begin(); channelIter != Server::channelList.end(); ++channelIter) {
				if (channelIter->_channel_name == channelVector[i]) {
					channelFound = true;
					for (std::list<User>::iterator userlistIter = channelIter->_userList.begin(); userlistIter != channelIter->_userList.end(); ++userlistIter) {
						if (user.getNickname() == userlistIter->getNickname()) {
							userFoundOnChannel = true;
							// delete user from channel
							for (list<User>::iterator usr_in_ch = channelIter->getUserList().begin(); usr_in_ch != channelIter->getUserList().end(); ++usr_in_ch)
								Service::sendMsg(user, *usr_in_ch, args[0], channelIter->getChannelName());
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
				Service::errMsg(403, user, channelVector[i]);
			} else if (!userFoundOnChannel) {
				Service::errMsg(442, user, args[1]);
			}
			channelFound = false;
			userFoundOnChannel = false;
		}
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
					cout << "channel is m: " << pair.first->_moderated << endl;
					cout << "user is v: " << pair.first->_voice << endl;
					if ((pair.first->_no_outside && !pair.first->inChannel(user))
						/*|| (pair.first->_moderated && !Service::isUserExist(pair.first.getVoiceList, user.getNickname()).second)*/)
						Service::errMsg(404, user, pair.first->getChannelName());
					else {
						for (list<User>::iterator ch_user = pair.first->_userList.begin(); ch_user != pair.first->_userList.end(); ++ch_user) {
							Service::sendMsg(user, *ch_user, args[0], pair.first->getChannelName(), args[2]);
							Bot::generateAnswer(user, args[2], args[0], pair.first->getChannelName());
						}
					}
				} else
					Service::errMsg(401, user, *it);
			} else {
				pair<list<User>::iterator, bool> pair = Service::isUserExist(*it);
				if (pair.second) {
					Service::sendMsg(user, *(pair.first), args[0], pair.first->getNickname(), args[2]);
					if (pair.first->isAway() && !isNotice)
						Service::replyMsg(301, user, pair.first->getNickname(), pair.first->getAutoReply());
				}
			}
		}
	}
}

void CommandList::quitCmd(User &user) {
	Server::kickUser(user);
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

//int CommandList::userCmd(vector<std::string> args, User &user) {
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

void CommandList::topicCmd(vector<string> args, User &user) {

	if (args.size() < 2) {
		Service::errMsg(461, user, args[0]);
		return;
	}
	pair<list<Channel>::iterator, bool> chPair = Service::isChannelExist(Server::channelList, args[1]);
	if (!chPair.second || !Service::isUserExist(chPair.first->_userList, user.getNickname()).second) {
		Service::errMsg(442, user, args[1]);
		return;
	}
	if (args.size() == 2) {
		if (chPair.first->getChannelTopic() != "")
			Service::replyMsg(332, user,chPair.first->getChannelName(), chPair.first->getChannelTopic());
		else
			Service::replyMsg(331, user,chPair.first->getChannelName());
	} else {
		if (chPair.first->_topic_by_oper && !Service::isUserExist(chPair.first->_operator_list, user.getNickname()).second)
			Service::errMsg(482, user, chPair.first->getChannelName());
		chPair.first->_topic = args[2];
		for (list<User>::iterator usr_in_ch = chPair.first->getUserList().begin(); usr_in_ch != chPair.first->getUserList().end(); ++usr_in_ch)
			Service::sendMsg(user, *usr_in_ch, args[0], chPair.first->getChannelName(), args[2]);
	}
}

void CommandList::wallopsCmd(vector<string> args, User &user) {
	if (args.size() < 2)
		Service::errMsg(461, user, args[0]);
	else {
		for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); ++it) {
			if (it->isOper())
				Service::sendMsg(user, *it, args[0], args[1]);
		}
	}
}

void CommandList::whoCmd(vector<string> args, User &user) {

	list<User>	wildCardUserlist;
	bool		operatorFlag = false;
	if (args.size() > 2 && args[2] == "o")
		operatorFlag = true;
	if (args.size() == 1 || (args.size() > 1 && args[1] == "0")) {
		for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
			if (it->isInvisible() && it->getNickname() == user.getNickname() && ((operatorFlag && it->isOper()) || !operatorFlag)) {
				vector<string> whoReplyVector = getWhoReplyVector(*it);
				Service::replyMsg(352, user, whoReplyVector[0], whoReplyVector[1], whoReplyVector[2], whoReplyVector[3], whoReplyVector[4], "H", to_string(0), whoReplyVector[5]);
			} else if (!it->isInvisible() && ((operatorFlag && it->isOper()) || !operatorFlag)) {
				vector<string> whoReplyVector = getWhoReplyVector(*it);
				Service::replyMsg(352, user, whoReplyVector[0], whoReplyVector[1], whoReplyVector[2], whoReplyVector[3], whoReplyVector[4], "H", to_string(0), whoReplyVector[5]);
			}
		}
	} else {
		CommandList::getWildcardChannelName(args[1], user, wildCardUserlist);
		if (wildCardUserlist.size() == 0) {
			CommandList::getWildcardHostName(args[1], user, wildCardUserlist);
			CommandList::getWildcardServerName(args[1], user, wildCardUserlist);
			CommandList::getWildcardRealName(args[1], user, wildCardUserlist);
			CommandList::getWildcardNickname(args[1], user, wildCardUserlist);
		}
		if (wildCardUserlist.size() > 0) {
			for (list<User>::iterator it = wildCardUserlist.begin(); it != wildCardUserlist.end(); it++) {
				if (((operatorFlag && it->isOper()) || !operatorFlag)) {
					vector<string> whoReplyVector = getWhoReplyVector(*it);
					Service::replyMsg(352, user, whoReplyVector[0], whoReplyVector[1], whoReplyVector[2], whoReplyVector[3], whoReplyVector[4], "H", to_string(0), whoReplyVector[5]);
				}
			}
		} else {
			Service::errMsg(403, user, args[0]);
		}
		Service::replyMsg(315, user, args[1]);
	}
}

vector<string>	CommandList::getWhoReplyVector(User &user) {

	vector<string> result;

	if (user.joinedChannels.size() > 0 && !Service::isChannelExist(user.joinedChannels.begin()->getChannelName()).first->_secret) {
		if (!Service::isChannelExist(user.joinedChannels.begin()->getChannelName()).first->_private)
			result.push_back(user.joinedChannels.begin()->getChannelName());
		else
			result.push_back("Prv");
	} else
		result.push_back("*no joined channels*");
	result.push_back(user.getUsername());
	result.push_back(user.getRealHost());
	result.push_back(user.getServername());
	result.push_back(user.getNickname());
	result.push_back(user.getRealName());

	return result;
}

void	CommandList::getWildcardNickname(string str, User &user, list<User> &userlist) {

	vector<string>	strVector = Service::split(str, '*');
	list<User>		wildCardUserList;
	string	username;
	bool	nameMatches = false;

	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
		nameMatches = false;
		username = it->getNickname();
		nameMatches = Service::match((char*)username.c_str(), (char*)str.c_str());
		if (nameMatches) {
			if (!Service::isUserExist(userlist, it->getNickname()).second && (!it->isInvisible()))
				userlist.push_back(*it);
			else if (!Service::isUserExist(userlist, it->getNickname()).second && (it->isInvisible() && it->getNickname() == user.getNickname()))
				userlist.push_back(*it);
		}
	}
}

void	CommandList::getWildcardChannelName(string str, User &user, list<User> &userlist) {

	string	username;
	string	channelName;
	bool	nameMatches;

	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
		for (list<Channel>::iterator cIt = it->joinedChannels.begin(); cIt != it->joinedChannels.end(); cIt++) {
			nameMatches = false;
			channelName = cIt->getChannelName();
			nameMatches = Service::match((char*)channelName.c_str(), (char*)str.c_str());
			if (nameMatches) {
				if (!Service::isUserExist(userlist, it->getNickname()).second && (!it->isInvisible()))
					userlist.push_back(*it);
				else if (!Service::isUserExist(userlist, it->getNickname()).second && (it->isInvisible() && it->getNickname() == user.getNickname()))
					userlist.push_back(*it);
				break;
			}
		}
	}
}

void	CommandList::getWildcardHostName(string str, User &user, list<User> &userlist) {

	string	realHostName;
	bool	nameMatches = false;


	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
		nameMatches = false;
		realHostName = it->getRealHost();
		nameMatches = Service::match((char*)realHostName.c_str(), (char*)str.c_str());
		if (nameMatches) {
			if (!Service::isUserExist(userlist, it->getNickname()).second && (!it->isInvisible()))
				userlist.push_back(*it);
			else if (!Service::isUserExist(userlist, it->getNickname()).second && (it->isInvisible() && it->getNickname() == user.getNickname()))
				userlist.push_back(*it);
		}
	}
}

void	CommandList::getWildcardServerName(string str, User &user, list<User> &userlist) {

	string	serverName;
	bool	nameMatches = false;


	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
		nameMatches = false;
		serverName = it->getServername();
		nameMatches = Service::match((char*)serverName.c_str(), (char*)str.c_str());
		if (nameMatches) {
			if (!Service::isUserExist(userlist, it->getNickname()).second && (!it->isInvisible()))
				userlist.push_back(*it);
			else if (!Service::isUserExist(userlist, it->getNickname()).second && (it->isInvisible() && it->getNickname() == user.getNickname()))
				userlist.push_back(*it);
		}
	}
}

void	CommandList::getWildcardRealName(string str, User &user, list<User> &userlist) {

	string	realName;
	bool	nameMatches = false;


	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
		nameMatches = false;
		realName = it->getRealName();
		nameMatches = Service::match((char*)realName.c_str(), (char*)str.c_str());
		if (nameMatches) {
			if (!Service::isUserExist(userlist, it->getNickname()).second && (!it->isInvisible()))
				userlist.push_back(*it);
			else if (!Service::isUserExist(userlist, it->getNickname()).second && (it->isInvisible() && it->getNickname() == user.getNickname()))
				userlist.push_back(*it);
		}
	}
}
