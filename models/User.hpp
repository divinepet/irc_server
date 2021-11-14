#pragma once

#include <iostream>
#include <string>

using namespace std;

class User {
	int     socket_fd;
	string  nickname, username, realName, host, servername, realHost;
	string  auto_reply;
	int     registerPhase;
	bool    validPass;
	bool    away;
	bool    registered;
	bool    oper;
    bool    invisible;
    bool    serv_notices;
    bool    wallops;

public:
	User(int _socket_fd);

	const string &getRealHost() const;

	void setRealHost(const string &realHost);

	User(const User& _x);
	User& operator=(const User& _x);
	bool operator == (const User& s) const { return socket_fd == s.socket_fd && nickname == s.nickname; }
	bool operator != (const User& s) const { return !operator==(s); }
	~User();

	void setValidPass(bool validPass);
	void setRegisterPhase(int registerPhase);
	void setUsername(const string &username);
	void setRealName(const string &realName);
	void setHost(const string &host);
	void setServername(const string &servername);
	void setNickname(const string &nickname);
	void setAutoReply(const string &autoReply);
	void setAway(bool value);
	void setOper(bool oper);

	int getSocketFd() const;
	int getRegisterPhase() const;
	const string &getUsername() const;
	const string &getRealName() const;
	const string &getHost() const;
	const string &getServername() const;
	const string &getNickname() const;
	const string &getAutoReply() const;

	bool isValidPass() const;
	bool isOper() const;
	bool isAway() const;
	bool isRegistered() const;
};
