#include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {}

bool Channel::addUser(User &user) {
    _userList.push_back(user);
    return true;
}

void Channel::deleteUser(User &user) {
    _userList.remove(user);
    _operator_list.remove(user);
}

void Channel::deleteOperator(User &user) {
    _operator_list.remove(user);
}

void Channel::sendToAll(User &sender, string channelName, string msg) {
	string prefix = ":" + sender.getNickname() + "!"
			+ sender.getUsername() + "@" + sender.getRealHost() + " MODE " + channelName + " ";
    for (list<User>::iterator it = _userList.begin(); it != _userList.end(); ++it) {
    	Server::writing(it->getSocketFd(), prefix + msg + "\n");
    }
}

bool Channel::addUser(User &user, string password) {

    if (password != _password) {
        Service::errMsg(475, user, _channel_name);
        return false;
    }
    _userList.push_back(user);
    return true;
}

void Channel::addUserToBanList(User &user) {
    if (!Service::isUserExist(_ban_list, user.getNickname()).second) {
        _ban_list.push_back(user);
    }
}

void Channel::addUserToInviteList(User &user) {
    if (!Service::isUserExist(_invite_list, user.getNickname()).second) {
        _invite_list.push_back(user);
    }
}

void Channel::addUserToVoiceList(User &user) {
    if (!Service::isUserExist(_voice_list, user.getNickname()).second) {
        _voice_list.push_back(user);
    }
}

void Channel::addOperator(User &user) {

    list<User>::iterator oper_iter = _operator_list.begin();

    for (; oper_iter != _operator_list.end() && user.getNickname() != oper_iter->getNickname(); ++oper_iter) {}
    if (oper_iter == _operator_list.end()) {
        _operator_list.push_back(user);
    }
}

bool Channel::inChannel(User user) {
	for (list<User>::iterator it = _userList.begin(); it != _userList.end(); ++it)
		if (*it == user) return true;
		return false;
}

bool Channel::isInviteOnly() const { return _invite_only; }

bool Channel::isPassword() const { return _has_password; }

string Channel::getChannelName() const { return _channel_name; }

string Channel::getChannelTopic() const { return _topic; }

list<User>& Channel::getOperList() { return _operator_list; }

list<User> &Channel::getBanList() { return _ban_list; }

list<User> &Channel::getVoiceList() { return _voice_list; }

list<User> &Channel::getUserList() { return _userList; }

list<User> &Channel::getInviteList() { return _invite_list; }

void Channel::setPrivateFlag(bool value) { _private = value; }

void Channel::setSecretFlag(bool value) { _secret = value; }

void Channel::setInviteFlag(bool value) { _invite_only = value; }

void Channel::setTopicFlag(bool value) { _topic_by_oper = value; }

void Channel::setOutsideFlag(bool value) { _no_outside = value; }

void Channel::setModeratedFlag(bool value) { _moderated = value; }

void Channel::setUserLimit(unsigned int value) { _user_limit = value; }

void Channel::setPassword(string pass) { _password = pass; _has_password = true; }

void Channel::resetPassword() { _password = ""; _has_password = false; }

bool Channel::isOperator(User &user) const {
	for (list<User>::const_iterator it = _operator_list.begin(); it != _operator_list.end(); ++it) {
		if (user.getNickname() == it->getNickname())
			return true;
	}
	return false;
}

bool Channel::isUserInvited(User &user) {
    if (!Service::isUserExist(_invite_list, user.getNickname()).second) {
        return false;
    }
    return true;
}

void Channel::muteAll() {
    for (list<User>::iterator it = _userList.begin(); it != _userList.end(); ++it) {
        addUserToVoiceList(*it);
    }
}

void Channel::unmuteAll() {
    for (list<User>::iterator it = _voice_list.begin(); it != _voice_list.end(); ++it) {
        _voice_list.remove(*it);
    }
}

void Channel::banAllNonMember() {
    for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); ++it) {
        if (!Service::isUserExist(_userList, it->getNickname()).second)
            addUserToBanList(*it);
    }
}


