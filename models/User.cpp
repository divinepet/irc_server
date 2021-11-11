#include "User.hpp"

User::~User() {}

User::User(int _socket_fd) : socket_fd(_socket_fd), registerPhase(0), away(false), registered(false), validPass(false) {}

User::User(const User &_x) : socket_fd(_x.socket_fd), nickname(_x.nickname), username(_x.username), realname(_x.realname),
								host(_x.host), servername(_x.servername), auto_reply(_x.auto_reply), registerPhase(_x.registerPhase),
								validPass(_x.validPass), away(_x.away), registered(_x.registered) {}

User &User::operator=(const User &_x) {
	if (this == &_x)
		return *this;
	socket_fd = _x.socket_fd;
	nickname = _x.nickname;
	username = _x.username;
	realname= _x.realname;
	host = _x.host;
	servername = _x.servername;
	auto_reply = _x.auto_reply;
	registerPhase = _x.registerPhase;
	validPass = _x.validPass;
	away = _x.away;
	registered = _x.registered;
	return *this;
}

int User::getSocketFd() const {	return socket_fd; }
int User::getRegisterPhase() const { return registerPhase; }
const string &User::getNickname() const { return nickname; }
const string &User::getAutoReply() const { return auto_reply; }
const string &User::getUsername() const { return username; }
const string &User::getRealname() const { return realname; }
const string &User::getHost() const { return host; }
const string &User::getServername() const { return servername; }
bool User::isRegistered() const { return registered; }
bool User::isAway() const { return away; }
bool User::isValidPass() const { return validPass; }

void User::setNickname(const string &nickname) { User::nickname = nickname; }
void User::setAutoReply(const string &autoReply) { auto_reply = autoReply; }
void User::setAway(bool value) { away = value; }
void User::setUsername(const string &username) { User::username = username; }
void User::setRealname(const string &realname) { User::realname = realname; }
void User::setHost(const string &host) { User::host = host; }
void User::setServername(const string &servername) { User::servername = servername; }
void User::setValidPass(bool validPass) { User::validPass = validPass; }
void User::setRegisterPhase(int registerPhase) {
	User::registerPhase = registerPhase;
	if (registerPhase == 3 && validPass) registered = true;
}












