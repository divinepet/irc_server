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

bool Channel::addUser(User &user, string password) {

    if (password != _password) {
        Service::errMsg(475, user, _channel_name);
        return false;
    }
    _userList.push_back(user);
    return true;
}

void Channel::addOperator(User &user) {

    list<User>::iterator oper_iter = _operator_list.begin();

    for (; oper_iter != _operator_list.end() && user.getNickname() != oper_iter->getNickname(); ++oper_iter) {}
    if (oper_iter == _operator_list.end()) {
        _operator_list.push_back(user);
    }
}

bool Channel::isInviteOnly() const { return _invite_only; }

bool Channel::isPassword() const { return _has_password; }

string Channel::getChannelName() const { return _channel_name; }

string Channel::getChannelTopic() const { return _topic; }

list<User>& Channel::getOperList() { return _operator_list; }

list<string> &Channel::getBanList() { return _ban_list; }

list<User>::iterator Channel::getOperListBegin() { return _operator_list.begin(); }

list<User>::iterator Channel::getOperListEnd() { return _operator_list.end(); }

bool Channel::inChannel(User user) {
	for (list<User>::iterator it = _userList.begin(); it != _userList.end(); ++it)
		if (*it == user) return true;
	return false;
}

void Channel::setPrivateFlag(bool value) { _private = value; }

void Channel::setSecretFlag(bool value) { _secret = value; }

void Channel::setInviteFlag(bool value) { _invite_only = value; }

void Channel::setTopicFlag(bool value) { _topic_by_oper = value; }

void Channel::setOutsideFlag(bool value) { _no_outside = value; }

void Channel::setModeratedFlag(bool value) { _moderated = value; }

void Channel::setUserLimit(unsigned int value) { _user_limit = value; }

void Channel::setVoiceFlag(bool value) { _voice = value; }

void Channel::setPassword(string pass) { _password = pass; _has_password = true; }

