#include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {}

void Channel::addUser(User &user) {
    _user_list.push_back(user);
}

void Channel::addUser(User &user, string password) {

    if (password != _password) {
        Service::errMsg(475, user, _channel_name);
    } else {
        _user_list.push_back(user);
    }
}