#include "User.hpp"

User::User() {}

User::~User() {}

User::User(int __socket_fd) : socket_fd(__socket_fd) , nickname(), auto_reply() {}

int User::getSocketFd() const {
	return socket_fd;
}

const string &User::getNickname() const {
	return nickname;
}

const string &User::getAutoReply() const {
	return auto_reply;
}

void User::setNickname(const string &nickname) {
	User::nickname = nickname;
}

void User::setAutoReply(const string &autoReply) {
	auto_reply = autoReply;
}

User::User(const User &__x) : socket_fd(__x.socket_fd), nickname(__x.nickname), auto_reply(__x.auto_reply) {}

User &User::operator=(const User &__x) {
	if (this == &__x)
		return *this;
	socket_fd = __x.socket_fd;
	nickname = __x.nickname;
	auto_reply = __x.auto_reply;
	return *this;
}

bool User::isRegistered() {
	return (!nickname.empty());
}
