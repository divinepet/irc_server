#pragma once

#include <iostream>
#include <string>
#include "Channel.hpp"

static int COUNTER;
using namespace std;

class Server;
class Channel;

class User {
	int		id; // unique id for every user for ping-pong commands
	int     socket_fd; // unique socket for every user for send message from server
	string  nickname, username, realName, host, servername, realHost;
	string  auto_reply;
	int     registerPhase; // count of register steps (user, pass and nick command passed)
	bool    validPass; // user was written correct server password
	bool    away;
	bool    registered; // for registration
	bool    oper; // check if user is operator of the SERVER (not channel)
    bool    invisible;
    bool    serv_notices;
    bool    wallops;

public:
	User(int _socket_fd);
	User(const User& _x);
	User& operator=(const User& _x);
	bool operator == (const User& s) const { return id == s.id; }
	bool operator != (const User& s) const { return !operator==(s); }
	~User();

	void setValidPass(bool validPass);
	void setRegisterPhase(int registerPhase);
	void setUsername(const string &username);
	void setRealName(const string &realName);
	void setRealHost(const string &realHost);
	void setHost(const string &host);
	void setServername(const string &servername);
	void setNickname(const string &nickname);
	void setAutoReply(const string &autoReply);
	void setAway(bool value);
	void setOper(bool oper);
    void setInvisible(bool value);
    void setWallops(bool value);
    void setNoticed(bool value);

	int getId() const;
	int getSocketFd() const;
	int getRegisterPhase() const;
	const string &getUsername() const;
	const string &getRealName() const;
	const string &getRealHost() const;
	const string &getHost() const;
	const string &getServername() const;
	const string &getNickname() const;
	const string &getAutoReply() const;
	bool isValidPass() const;
	bool isOper() const;
	bool isAway() const;
	bool isRegistered() const;
	bool isInvisible() const;
	list<Channel>	joinedChannels;
};
