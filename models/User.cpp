#include "User.hpp"

User::~User() {}

User::User(int _socket_fd) : socket_fd(_socket_fd), registerPhase(0), away(false), registered(false), validPass(false),
								oper(false), invisible(false), serv_notices(true), wallops(true) {}

User::User(const User &_x) : socket_fd(_x.socket_fd), nickname(_x.nickname), username(_x.username), realName(_x.realName),
								host(_x.host), servername(_x.servername), realHost(_x.realHost), auto_reply(_x.auto_reply),
								registerPhase(_x.registerPhase), validPass(_x.validPass), away(_x.away),
								registered(_x.registered), oper(_x.oper), wallops(_x.wallops), serv_notices(_x.serv_notices),
                                invisible(_x.invisible) {}

User &User::operator=(const User &_x) {
	if (this == &_x)
		return *this;

	socket_fd = _x.socket_fd;
	nickname = _x.nickname;
	username = _x.username;
	realName= _x.realName;
	host = _x.host;
	servername = _x.servername;
	realHost = _x.realHost;
	auto_reply = _x.auto_reply;
	registerPhase = _x.registerPhase;
	validPass = _x.validPass;
	away = _x.away;
	registered = _x.registered;
	oper = _x.oper;
    wallops = _x.wallops;
    serv_notices = _x.serv_notices;
    invisible = _x.invisible;
	return *this;
}

int User::getSocketFd() const {	return socket_fd; }
int User::getRegisterPhase() const { return registerPhase; }
const string &User::getNickname() const { return nickname; }
const string &User::getAutoReply() const { return auto_reply; }
const string &User::getUsername() const { return username; }
const string &User::getRealName() const { return realName; }
const string &User::getHost() const { return host; }
const string &User::getServername() const { return servername; }
const string &User::getRealHost() const { return realHost; }
bool User::isRegistered() const { return registered; }
bool User::isAway() const { return away; }
bool User::isValidPass() const { return validPass; }
bool User::isOper() const { return oper; }

void User::setNickname(const string &nickname) { User::nickname = nickname; }
void User::setAutoReply(const string &autoReply) { auto_reply = autoReply; }
void User::setAway(bool value) { away = value; }
void User::setUsername(const string &username) { User::username = username; }
void User::setRealName(const string &realName) { User::realName = realName; }
void User::setHost(const string &host) { User::host = host; }
void User::setServername(const string &servername) { User::servername = servername; }
void User::setValidPass(bool validPass) { User::validPass = validPass; }
void User::setOper(bool oper) { User::oper = oper; }
void User::setRealHost(const string &realHost) { User::realHost = realHost; }
void User::setRegisterPhase(int registerPhase) {
	User::registerPhase = registerPhase;
	if (registerPhase == 3 && validPass) registered = true;
}
















