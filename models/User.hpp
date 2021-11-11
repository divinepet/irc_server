#pragma once

#include <iostream>
#include <string>

using namespace std;

class User {
	int socket_fd;
	string nickname, username, realname, host, servername;
	string auto_reply;
	int registerPhase;
	bool validPass;
	bool away;
	bool registered;
	User() {};
public:
	User(int _socket_fd);
	User(const User& _x);
	User& operator=(const User& _x);
	bool operator == (const User& s) const { return socket_fd == s.socket_fd && nickname == s.nickname; }
	bool operator != (const User& s) const { return !operator==(s); }
	~User();

	void setValidPass(bool validPass);

	void setRegisterPhase(int registerPhase);
	void setUsername(const string &username);
	void setRealname(const string &realname);
	void setHost(const string &host);
	void setServername(const string &servername);
	void setNickname(const string &nickname);
	void setAutoReply(const string &autoReply);
	void setAway(bool value);

	int getSocketFd() const;
	int getRegisterPhase() const;
	const string &getUsername() const;
	const string &getRealname() const;
	const string &getHost() const;
	const string &getServername() const;
	const string &getNickname() const;
	const string &getAutoReply() const;

	bool isValidPass() const;

	bool isAway() const;
	bool isRegistered() const;
};