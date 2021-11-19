
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

	string                              rqsted_user;
	string                              rqsted_chnl_name;
	pair<list<User>::iterator, bool>    usr_iter;// = Server::userList.begin();
	pair<list<User>::iterator, bool>    chnl_usr_list;// = chnl_iter.first->_userList.begin();
    pair<list<User>::iterator, bool>    chnl_oper_list;// = chnl_iter->_operator_list.begin();
    pair<list<Channel>::iterator, bool> chnl_iter;// = Server::channelList.begin();

	if (args.size() > 2) {
		rqsted_user = args[1];
		rqsted_chnl_name = args[2];
		chnl_iter = Service::isChannelExist(rqsted_chnl_name); // searching rqsted channel
		if (chnl_iter.second) { // if rqsted channel exists
		    usr_iter = Service::isUserExist(rqsted_user); // searching rqsted user
			if (usr_iter.second) { // if rqsted user exists
				if (Service::isUserExist(chnl_iter.first->getUserList(), user.getNickname()).second) { // if current user on rqsted channel
					if (!Service::isUserExist(chnl_iter.first->getUserList(), rqsted_user).second) { // if rqsted user NOT on rqsted channel
						if (chnl_iter.first->isInviteOnly()) { // if rqsted channel is invite only
							if (!Service::isUserExist(chnl_iter.first->getOperList(), user.getNickname()).second) { // cuurent user not operator on invite only channel
								Service::errMsg(482, user,rqsted_chnl_name);
								return ;
							}
						}
						if (!usr_iter.first->isAway()) { // rqsted user is available
							chnl_iter.first->addUserToInviteList(*usr_iter.first);
							// usr_iter.first->addInvitedChnl(*chnl_iter.first);
							Service::replyMsg(341, user, rqsted_chnl_name, rqsted_user);
							Service::sendMsg(user, *usr_iter.first, args[0], usr_iter.first->getNickname(), rqsted_chnl_name);
						} else { // rqsted user has AWAY status
							Service::replyMsg(301, user, rqsted_user, usr_iter.first->getAutoReply());
						}
					} else { // rqsted user already on channel
						Service::errMsg(443, user, rqsted_user, rqsted_chnl_name);
					}
				} else { // current user not on rqsted channel
					Service::errMsg(442, user, rqsted_chnl_name);
				}
			} else { // rqsted user does not exist
				Service::errMsg(401, user, rqsted_user);
			}
		} else { //rqsted channel does not exist
		    Service::errMsg(403, user, rqsted_chnl_name);
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
			if (Service::isChannelName(input_channels[i])) { // if chnl name is valid
				chnl = Service::isChannelExist(input_channels[i]); // searching new chnl among the existing
				if (!chnl.second) { // if rqsted chnl does not exist
				    if (!input_passwords.empty() && input_passwords[i].length() > 0) { // input_passwords.size() > i &&
						new_chnl = Channel(input_channels[i], user, input_passwords[i]);
					} else {
						new_chnl = Channel(input_channels[i], user);
					}
					new_chnl.addOperator(user);
					Server::channelList.push_back(new_chnl);
					user.joinedChannels.push_back(new_chnl);
					Service::sendMsg(user, user, args[0], new_chnl.getChannelName());
					Service::replyMsg(331, user, new_chnl.getChannelName(), new_chnl.getChannelTopic());
					Service::replyMsg(353, user, "= " + new_chnl.getChannelName(), "@" + user.getNickname());
					Service::replyMsg(366, user, new_chnl.getChannelName());
				} else { // if rqsted chnl exist
					if (!Service::isUserExist(chnl.first->getUserList(), user.getNickname()).second) { // if user not on rqsted chnl
						if (!Service::isUserExist(chnl.first->getBanList(), user.getNickname()).second) { // if user not banned on chnl
							if (!chnl.first->isInviteOnly() || (chnl.first->isInviteOnly() && chnl.first->isUserInvited(user))) { // if rqsted chnl (is NOT invite_only || is invite_only and user has been invited)
							    if (!chnl.first->isPassword()) { // if rqsted chnl is NOT protected by password
							        res = chnl.first->addUser(user);
							    } else { // rqsted chnl is protected by password
							        if (!input_passwords.empty() && input_passwords[i].length() > 0) { // if password is passed
							            res = chnl.first->addUser(user, input_passwords[i]);
							        }
							        else {  // password NOT passed
							            Service::errMsg(475, user,chnl.first->getChannelName());
							            return ;
							        }
							    }
							    if (res) { // if addUser is succesfull
							        user.joinedChannels.push_back(*chnl.first);
							        for (list<User>::iterator usr_in_ch = chnl.first->getUserList().begin(); usr_in_ch != chnl.first->getUserList().end(); ++usr_in_ch)
							            Service::sendMsg(user, *usr_in_ch, args[0], chnl.first->getChannelName());
							        if (chnl.first->getChannelTopic() != "")
							        	Service::replyMsg(332, user, chnl.first->getChannelName(), chnl.first->getChannelTopic());
							        else
							        	Service::replyMsg(331, user, chnl.first->getChannelName());
							        Service::replyMsg(353, user, "= " + chnl.first->getChannelName(),Service::to_string(chnl.first->getOperList(), true)
							        + Service::to_string(chnl.first->getUserList(), *(chnl.first)));
							        Service::replyMsg(366, user, chnl.first->getChannelName());
							    }
							} else { // rqsted chnl is invite only
								Service::errMsg(473, user, chnl.first->_channel_name);
							}
						} else { // user banned on chnl
							Service::errMsg(474, user, input_channels[i]);
						}
					} else { // user already on rqsted chnl
						Service::errMsg(443, user, chnl.first->getChannelName());
					}
				}
			} else { // chnl name is invalid
				Service::errMsg(403, user, input_channels[i]);
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
	bool	kickedUserFoundOnChannel = false;
	bool	userFoundOnChannel = false;
	bool	userIsOperator = false;

	if (args.size() > 2) {
		channelVector = Service::split(args[1], ',');
		userVector = Service::split(args[2], ',');
		int channelVectorSize = channelVector.size();
		if (channelVectorSize != userVector.size())
		{
			Service::errMsg(461, user, "KICK");
			return ;
		}
		for (int i = 0; i < channelVectorSize; i++) {
			std::list<Channel>::iterator channelIter; // Check channels
			for (channelIter = Server::channelList.begin(); channelIter != Server::channelList.end(); ++channelIter) {
				if (channelIter->_channel_name == channelVector[i]) {
					channelFound = true;
					if (Service::isUserExist(channelIter->getUserList(), user.getNickname()).second)
						userFoundOnChannel = true;
					if (Service::isUserExist(channelIter->getOperList(), user.getNickname()).second)
						userIsOperator = true;
					for (std::list<User>::iterator userlistIter = channelIter->_userList.begin(); userIsOperator && userlistIter != channelIter->_userList.end(); ++userlistIter) {
						if (userVector[i] == userlistIter->getNickname()) {
							kickedUserFoundOnChannel = true;
							// delete user from channel
                            string comment = user.getNickname();
                            if (args.size() > 3)
                                comment = args[3];
							for (list<User>::iterator usr_in_ch = channelIter->getUserList().begin(); usr_in_ch != channelIter->getUserList().end(); ++usr_in_ch)
								Service::sendMsg(user, *usr_in_ch, args[0], channelIter->getChannelName(), args[2] + " :" + comment);
							/* Check for last operator */
							if (Service::isUserExist(channelIter->_operator_list, user.getNickname()).second
							&& channelIter->_operator_list.size() == 1 && channelIter->_userList.size() != 1 && user.getNickname() == args[2]) {
								User usr = *(++channelIter->_userList.begin());
								channelIter->addOperator(usr);
								Service::sendMsg(user, usr, "MODE", channelIter->getChannelName(), usr.getNickname() + " is operator now");
							}
							Service::deleteChannelFromUser(*userlistIter, *channelIter);
                            channelIter->deleteUser(*userlistIter);
							Server::channelList.remove_if(Service::channelIsEmpty);
							break ;
						}
					}
					if (kickedUserFoundOnChannel)
						break ;
				}
			}
			if (!channelFound) {
				Service::errMsg(403, user, args[1]);
			} else if (!userFoundOnChannel) {
				Service::errMsg(442, user, channelIter->_channel_name);
			} else if (!userIsOperator) {
				Service::errMsg(482, user, channelIter->_channel_name);
			}
			else if (!kickedUserFoundOnChannel) {
				Service::errMsg(401, user, args[1]);
			}
			channelFound = false;
			kickedUserFoundOnChannel = false;
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
                        Service::errMsg(472, user, string(1, args[2][i]));
                        return false;
                    }
                    if (args[2][i] == 'o' || args[2][i] == 'l' || args[2][i] == 'v') {
                        special_flags = true;
                    }
                }
                if (special_flags && args[2].length() > 2) { // if flags [o l b k] not single in line
                    Service::errMsg(472, user, args[2]);
                    return false;
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
                        Service::errMsg(472, user, args[2]);
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

void CommandList::setChnlModeOperator(vector<string> args, User &user, Channel &rqsted_chnl) {

    string                              msg;
    pair<list<User>::iterator, bool>    rqsted_user;

    rqsted_user = Service::isUserExist(args[3]);
    if (rqsted_user.second) { // if input user exist
        if (Service::isUserExist(rqsted_chnl.getUserList(), rqsted_user.first->getNickname()).second) { // if rqsted user on rqsted chnl
            if (Service::isUserExist(rqsted_chnl.getOperList(), args[3]).second) { // if input user not operator yet on rqsted channel
                if (args[2][0] == '+') {
                    Service::replyMsg(221,user, args[3] + " is already operator");
                } else {
                    msg = args[3] + " removed from operator list";
                    rqsted_chnl.deleteOperator(*rqsted_user.first);
                    rqsted_chnl.sendToAll(user, args[1], msg);
                }
            } else {
                if (args[2][0] == '+') {
                    msg = args[3] + " is operator now";
                    rqsted_chnl.addOperator(*rqsted_user.first);
                    rqsted_chnl.sendToAll(user, args[1], msg);
                } else {
                    Service::replyMsg(221,user, args[3] + " is already not an operator on ");
                }
            }
        } else { // rqsted user not on rqsted chnl
            Service::errMsg(441, user, rqsted_user.first->getNickname(), rqsted_chnl.getChannelName());
        }
    } else { // NO such user
        Service::errMsg(401, user, args[3]);
    }
}

void CommandList::setChnlModePrivate(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') {
        msg = "private channel is enabled";
        rqsted_chnl.setPrivateFlag(true);
    } else {
        msg = "private channel is disabled";
        rqsted_chnl.setPrivateFlag(false);
    }
    rqsted_chnl.sendToAll(user, args[1], msg);
}

void CommandList::setChnlModeSecret(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') {
    	msg = "secret channel is enabled";
        rqsted_chnl.setSecretFlag(true);
    } else {
    	msg = "secret channel is disabled";
        rqsted_chnl.setSecretFlag(false);
    }
    rqsted_chnl.sendToAll(user, args[1], msg);
}

void CommandList::setChnlModeInvite(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') {
    	msg = "invite only is enabled";
        rqsted_chnl.setInviteFlag(true);
    } else {
    	msg = "invite only is disabled";
        rqsted_chnl.setInviteFlag(false);
    }
    rqsted_chnl.sendToAll(user, args[1], msg);
}

void CommandList::setChnlModeTopic(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') {
    	msg = "topic set by operator is enabled";
        rqsted_chnl.setTopicFlag(true);
    } else {
    	msg = "topic set by operator is disabled";
        rqsted_chnl.setTopicFlag(false);
    }
    rqsted_chnl.sendToAll(user, args[1], msg);
}

void CommandList::setChnlModeOutside(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') {
    	msg = "messages from only channel clients is enabled";
        rqsted_chnl.setOutsideFlag(true);
    } else {
    	msg = "messages from only channel clients is disabled";
        rqsted_chnl.setOutsideFlag(false);
    }
    rqsted_chnl.sendToAll(user, args[1], msg);
}

void CommandList::setChnlModeModerated(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') {
        msg = "read only channel mode is enabled";
        rqsted_chnl.setModeratedFlag(true);
        rqsted_chnl.muteAll();
    } else {
    	msg = "read only channel mode is disabled";
        rqsted_chnl.setModeratedFlag(false);
        rqsted_chnl.unmuteAll();
    }
    rqsted_chnl.sendToAll(user, args[1], msg);
}

void CommandList::setChnlModeLimit(vector<string> args, User &user, Channel &rqsted_chnl) {

    string          msg;
    unsigned int    result;

    for (size_t i = 0; i < args[3].length(); ++i) {
        if (args[2][0] == '-' || args[3][0] == '0' || !isnumber(args[3][i])) {
            Service::errMsg(501, user, args[3]);
            return ;
        }
    }
    try {
        result = stoi(args[3]);
        msg = "user limit is " + to_string(result) + "now";
        rqsted_chnl.setUserLimit(result);
        rqsted_chnl.sendToAll(user, args[1], msg);
    } catch (std::exception) {
        Service::errMsg(501, user, args[3]);
        return;
    }
}

void CommandList::setChnlModeBan(vector<string> args, User &user, Channel &rqsted_chnl) {

    string                              msg;
    list<User>                          ban_list = rqsted_chnl.getBanList();
    pair<list<User>::iterator, bool>    rqsted_user;

    rqsted_user = Service::isUserExist(args[3]);
    if (rqsted_user.second) { // if rqsted user exists
        if (Service::isUserExist(rqsted_chnl.getUserList(), args[3]).second) { // if rqsted user on rqasted chnl
            if (args[2][0] == '+') { // +b
                if (args.size() > 3) { // +b with params
                    if (args[3] == "*!*@*") {
                        msg = args[3] + " all non member users have been banned";
                        rqsted_chnl.banAllNonMember();
                        rqsted_chnl.sendToAll(user, args[1], msg);
                    } else if (!Service::isUserExist(rqsted_chnl.getBanList(), args[3]).second) { // if rqsted user NOT in ban list
                        msg = args[3] + " has been banned";
                        rqsted_chnl.addUserToBanList(*rqsted_user.first);
                        rqsted_chnl.sendToAll(user, args[1], msg);
                    } else { // rqsted user already in ban list
                        Service::replyMsg(221, user, args[3] + " is already banned on");
                    }
                } else { // single +b
                    for (list<User>::iterator it = ban_list.begin(); it != ban_list.end(); ++it) {
                        Service::replyMsg(367, user, rqsted_chnl.getChannelName() + it->getNickname());
                    }
                    Service::replyMsg(368, user, rqsted_chnl.getChannelName());
                }
            } else { // -b
                if (Service::isUserExist(rqsted_chnl.getBanList(), args[3]).second) { // if rqsted user exist in ban list
                    msg = args[3] + " has been unbanned";
                    rqsted_chnl.getBanList().remove(*rqsted_user.first);
                    rqsted_chnl.sendToAll(user, args[1], msg);
                } else { // rqsted user already in mute list
                    Service::replyMsg(221, user, args[3] + " is already unbanned on");
                }
            }
        } else { // rqsted user not on rqsted chnl
            Service::errMsg(442, *rqsted_user.first, rqsted_chnl.getChannelName());
        }
    } else { // rqsted user not found
        Service::errMsg(401, user, args[4]);
    }
}

void CommandList::setChnlModeVoice(vector<string> args, User &user, Channel &rqsted_chnl) {

    string                              msg;
    pair<list<User>::iterator, bool>    rqsted_user;

    rqsted_user = Service::isUserExist(args[3]);
    if (rqsted_user.second) { // if rqsted user exists
        if (Service::isUserExist(rqsted_chnl.getUserList(), args[3]).second) { // if rqsted user on rqasted chnl
            if (args[2][0] == '+') { // +v
                if (!Service::isUserExist(rqsted_chnl.getVoiceList(), args[3]).second) { // if rqsted user NOT in mute list
                    msg = args[3] + " has voice now";
                    rqsted_chnl.addUserToVoiceList(*rqsted_user.first);
                    rqsted_chnl.sendToAll(user, args[1], msg);
                } else { // rqsted user already in mute list
                    Service::replyMsg(221, user, args[3] + " is already has voice");
                }
            } else { // -v
                if (Service::isUserExist(rqsted_chnl.getVoiceList(), args[3]).second) { // if rqsted user exist in mute list
                    msg = args[3] + " has been muted";
                    rqsted_chnl.getVoiceList().remove(*rqsted_user.first);
                    rqsted_chnl.sendToAll(user, args[1], msg);
                } else { // rqsted user already in mute list
                    Service::replyMsg(221, user, args[3] + " is already no voice");
                }
            }
        } else { // rqsted user not on rqsted chnl
            Service::errMsg(442, *rqsted_user.first, rqsted_chnl.getChannelName());
        }
    } else { // rqsted user not found
        Service::errMsg(401, user, args[3]);
    }
}

void CommandList::setChnlModeKey(vector<string> args, User &user, Channel &rqsted_chnl) {
    string  msg;

    if (args[2][0] == '+') { // +k
        if (args.size() > 3) { // +k with params
            if (!rqsted_chnl.isPassword()) { // no password on chnl
                msg = "channel has been protected with key: " + args[3];
                rqsted_chnl.setPassword(args[3]);
                rqsted_chnl.sendToAll(user, args[1], msg);
            } else { // chnl key is already set
                Service::errMsg(467, user, rqsted_chnl.getChannelName());
            }
        } else { // not enough params for +k
            Service::errMsg(472, user, args[2]);
        }
    } else { // -k
        msg = "channel key has been removed";
        rqsted_chnl.resetPassword();
        rqsted_chnl.sendToAll(user, args[1], msg);
    }
}

void CommandList::setUserModeInvisible(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        user.setInvisible(true);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "invisible mode is enabled");
    } else {
        user.setInvisible(false);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "invisible mode is disabled");
    }
}

void CommandList::setUserModeNoticed(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        user.setNoticed(true);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "reception_notices_from_server mode is enabled");
    } else {
        user.setNoticed(false);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "reception_notices_from_server mode is disabled");
    }
}

void CommandList::setUserModeWallops(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        user.setWallops(true);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "reception_wallops mode is enabled");
    } else {
        user.setWallops(false);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "reception_wallops mode is disabled");
    }
}

void CommandList::setUserModeOperator(vector<string> args, User &user) {
    if (args[2][0] == '+') {
        Service::errMsg(472, user, "+o");
    } else {
        user.setOper(false);
        Service::sendMsg(user, user, args[0] + user.getNickname() + "operator mode is disabled");
    }
}

void CommandList::setChnlMode(vector<string> args, User &user, Channel &chnl) {
    for (size_t i = 1; i < args[2].length(); ++i) {
        switch (args[2][i]) {
            case 'o': {
                setChnlModeOperator(args, user, chnl);
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

void CommandList::modeCmd(vector<string> args, User &user) {
    pair<list<User>::iterator, bool>    rqsted_user;
    pair<list<Channel>::iterator, bool> rqsted_chnl;

    if (checkModeParams(args, user)) {
        if (args[1][0] == '#' || args[1][0] == '&') { // if MODE fot channel
            rqsted_chnl = Service::isChannelExist(args[1]);
            if (rqsted_chnl.second) { // if rqsted channel exist
                if (Service::isUserExist(rqsted_chnl.first->getOperList(), user.getNickname()).second) { // if cuurent user operator on rqsted channel
                    setChnlMode(args, user, *rqsted_chnl.first);
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

void CommandList::namesCmd(vector<string> args, User &user) {

	std::vector<std::string> channelVector;
	if (args.size() == 1) {
		for (list<Channel>::iterator ch = Server::channelList.begin(); ch != Server::channelList.end(); ch++) {
			if (ch->_private || ch->_secret) {
				if (Service::isChannelExist(user.joinedChannels, ch->getChannelName()).second) { // if user is in channel
					string userlist = Service::getUsersFromList(user, ch->_userList, *ch);
					Service::replyMsg(353, user, "= " + ch->getChannelName(), userlist);
				}
			} else {
				string userlist = Service::getUsersFromList(user, ch->_userList, *ch);
				Service::replyMsg(353, user, "= " + ch->getChannelName(), userlist);
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
						Service::replyMsg(353, user, "= " + kex.first->getChannelName(), userlist);
					}
				} else {
					string userlist = Service::getUsersFromList(user, kex.first->_userList, *kex.first);
					Service::replyMsg(353, user, "= " + kex.first->getChannelName(), userlist);
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
	if (!user.getNickname().empty())
		Server::userHistory.push_back(user);

	user.setNickname(args[1]);
	user.setRegisterPhase(user.getRegisterPhase() + 1);
	if (user.getRegisterPhase() == 2 && !user.isValidPass()) {
		Server::kickUser(user);
		return 0;
	}
	if (user.getRegisterPhase() == 3 && user.isValidPass()) { motd(user); return 7; }
	return 0;

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
							/* Check for last operator */
							if (Service::isUserExist(channelIter->_operator_list, user.getNickname()).second
							&& channelIter->_operator_list.size() == 1 && channelIter->_userList.size() != 1) {
								User usr = *(++channelIter->_userList.begin());
								channelIter->addOperator(usr);
								Service::sendMsg(user, usr, "MODE", channelIter->getChannelName(), usr.getNickname() + " is operator now");
							}
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

void CommandList::passCmd(vector<string> args, User &user, string pass) {
	if (user.isRegistered()) {
		Service::errMsg(462, user);
		return;
	} else if (user.getRegisterPhase() == 2) {
		Server::kickUser(user);
		return;
	}
	if (args[1] == pass) {
		user.setValidPass(true);
		user.setRegisterPhase(user.getRegisterPhase() + 1);
	}
}

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
	else if (args[2].find("DCC SEND") != string::npos)
		Service::sendFile(args[2]);
	else {
		vector<string> arg_list = Service::split(args[1], ',');
		for (vector<string>::iterator it = arg_list.begin(); it != arg_list.end(); ++it) {
			if (it->front() == '#' || it->front() == '&') {
				pair<list<Channel>::iterator, bool> pair = Service::isChannelExist(*it);
				if (pair.second) {
					if ((pair.first->_no_outside && !pair.first->inChannel(user))
						|| (pair.first->_moderated && !Service::isUserExist(pair.first->getVoiceList(), user.getNickname()).second))
						Service::errMsg(404, user, pair.first->getChannelName());
					else {
						for (list<User>::iterator ch_user = pair.first->_userList.begin(); ch_user != pair.first->_userList.end(); ++ch_user) {
                            if (user.getNickname() == ch_user->getNickname()) {
                                continue ;
                            }
                            Service::sendMsg(user, *ch_user, args[0], pair.first->getChannelName(), args[2]);
                        }
                        Bot::generateAnswer(user, args[2], args[0], pair.first->getChannelName());
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

int CommandList::userCmd(vector<std::string> args, User &user) {
	if (args.size() < 4) {
		Service::errMsg(461, user);
		return 0;
	}
	user.setUsername(args[1]);
	user.setHost(args[2]);
	user.setServername(args[3]);
	user.setRealName(args[4]);
	user.setRegisterPhase(user.getRegisterPhase() + 1);
	if (user.getRegisterPhase() == 2 && !user.isValidPass()) { Server::kickUser(user); return 0; }
	if (user.getRegisterPhase() == 3 && user.isValidPass()) { motd(user); return 7; }
	return 0;
}

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
			Service::replyMsg(331, user, chPair.first->getChannelName());
	} else {
		if (chPair.first->_topic_by_oper && !Service::isUserExist(chPair.first->_operator_list, user.getNickname()).second)
			Service::errMsg(482, user, chPair.first->getChannelName());
		else {
			chPair.first->_topic = args[2];
			for (list<User>::iterator usr_in_ch = chPair.first->getUserList().begin(); usr_in_ch != chPair.first->getUserList().end(); ++usr_in_ch)
				Service::sendMsg(user, *usr_in_ch, args[0], chPair.first->getChannelName(), args[2]);
		}
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

void CommandList::whoWasCmd(vector<string> args, User &user) {
	if (args.size() == 1) {
		Service::errMsg(431, user);
		return;
	}
	vector<string> searchingNicknames = Service::split(args[1], ',');
	size_t count = (args.size() > 2) ? atoi(args[2].c_str()) : searchingNicknames.size();
	vector<User> results;
	bool isFound;
	for (size_t i = 0; i < searchingNicknames.size(); ++i) { // lol, lol2
		isFound = false;							// lol, lol2
		for (list<User>::iterator usrIt = Server::userHistory.begin(); usrIt != Server::userHistory.end(); ++usrIt) {
			if (usrIt->getNickname() == searchingNicknames[i]) {
				results.push_back(*usrIt);
				isFound = true;
			}
		}
		if (!isFound) Service::errMsg(406, user, searchingNicknames[i]);
	}
	for (vector<User>::iterator it = results.begin(); it != results.end() && count > 0; ++it, count--) {
		Service::replyMsg(314, user, it->getNickname(), it->getUsername(), it->getRealHost(), it->getRealName());
	}
	Service::replyMsg(369, user, args[1]);
}

void CommandList::whoisCmd(vector<string> args, User &user) {

	vector<string>	splittedUserlist;

	if (args.size() > 1) {
		splittedUserlist = Service::split(args[1], ',');
		for (size_t i = 0; i < splittedUserlist.size(); i++) {
			list<User>		resultUserlist;
			CommandList::getWildcardNickname(splittedUserlist[i], user, resultUserlist);
			for (list<User>::iterator it = resultUserlist.begin(); it != resultUserlist.end(); it++) {
				uint64_t afk = (Service::timer() - Server::rr_data[it->getId()].last_message_time) / 1000;
				Service::replyMsg(311, user, it->getNickname(), it->getUsername(), it->getRealHost(), it->getRealName());
				if (it->isAway())
					Service::replyMsg(301, user, it->getNickname(), it->getAutoReply());
				if (it->isOper())
					Service::replyMsg(313, user, it->getNickname());
				Service::replyMsg(317, user, it->getNickname(), to_string(afk));
				string joinedChannels = CommandList::getJoinedChannelsString(*Service::isUserExist(it->getNickname()).first, user);
				if (joinedChannels.size() != 0)
					Service::replyMsg(319, user, it->getNickname(), joinedChannels);
				Service::replyMsg(318, user, it->getNickname());
			}
			if (resultUserlist.size() == 0)
				Service::errMsg(401, user, splittedUserlist[i]);
		}
	} else {
		Service::errMsg(431, user);
	}
}

vector<string> CommandList::getWhoReplyVector(User &user) {

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

string	CommandList::getJoinedChannelsString(User &user, User &initiator) {

	std::string		result;

	for (list<Channel>::iterator it = user.joinedChannels.begin(); it != user.joinedChannels.end(); it++) {
		if (!Service::isChannelExist(user.joinedChannels.begin()->getChannelName()).first->_secret) {
			if (!Service::isChannelExist(it->getChannelName()).first->_private) {
				if (Service::isUserExist(Service::isChannelExist(it->getChannelName()).first->getOperList(), user.getNickname()).second)
					result += "[@]";
				result += CommandList::channelFlags(*it) + it->getChannelName() + ' ';
			} else if (Service::isChannelExist(initiator.joinedChannels, it->getChannelName()).second) {
				if (Service::isUserExist(Service::isChannelExist(it->getChannelName()).first->getOperList(), user.getNickname()).second)
					result += "[@]";
				result += CommandList::channelFlags(*it) + it->getChannelName() + ' ';
			} else {
				result += "Prv ";
			}
		} else if (Service::isChannelExist(initiator.joinedChannels, it->getChannelName()).second) {
			if (Service::isUserExist(Service::isChannelExist(it->getChannelName()).first->getOperList(), user.getNickname()).second)
				result += "[@]";
			result += CommandList::channelFlags(*it) + it->getChannelName() + ' ';
		}
	}
	return result;
}

string	CommandList::channelFlags(Channel &channel)  {

	list<Channel>::iterator globalScopeChannel = Service::isChannelExist(channel.getChannelName()).first;
	string result;

	if (globalScopeChannel->isInviteOnly()) {
		result += 'i';
	}
	if (globalScopeChannel->_moderated) {
		result += 'm';
	}
	if (globalScopeChannel->_topic_by_oper) {
		result += 't';
	}
	if (globalScopeChannel->_no_outside) {
		result += 'n';
	}
	if (globalScopeChannel->_private) {
		result += 'p';
	}
	if (globalScopeChannel->_has_password) {
		result += 'k';
	}
	if (result.size() > 0) {
		result = "[+" + result + "]";
	}
	return result;
}

void CommandList::getWildcardNickname(string str, User &user, list<User> &userlist) {

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

void CommandList::getWildcardChannelName(string str, User &user, list<User> &userlist) {

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

void CommandList::getWildcardHostName(string str, User &user, list<User> &userlist) {

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

void CommandList::getWildcardServerName(string str, User &user, list<User> &userlist) {

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

void CommandList::getWildcardRealName(string str, User &user, list<User> &userlist) {

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
