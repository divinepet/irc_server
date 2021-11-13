#include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {}

bool Channel::addUser(User &user) {
    _user_list.push_back(user);
    return true;
}

void Channel::deleteUser(User &user) {
    _user_list.remove(user);
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
    _user_list.push_back(user);
    return true;
}

void Channel::addOperator(User &user) {

    list<User>::iterator usr_iter = _user_list.begin();

    for (; usr_iter != _user_list.end() && user.getNickname() != usr_iter->getNickname(); ++usr_iter) {}
    if (usr_iter == _user_list.end()) {
        _user_list.push_back(user);
    }
}

bool Channel::isInviteOnly() const { return _invite_only; }

string Channel::getChannelName() const { return _channel_name; }

string Channel::getChannelTopic() const { return _topic; }

list<User>::iterator Channel::getOperListBegin() { return _operator_list.begin(); }

list<User>::iterator Channel::getOperListEnd() { return _operator_list.end(); }


