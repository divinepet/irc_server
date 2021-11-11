#include "Channel.hpp"

Channel::Channel() {}

Channel::~Channel() {}

void Channel::addUser(User &user) {
    _user_list.push_back(user);
}