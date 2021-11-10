#pragma once

#include <iostream>
#include <string>

using namespace std;

class User {
	int socket_fd;
	string nickname;
	string auto_reply;
	User();
public:
	User(int __socket_fd);
	User(const User& __x);
	User& operator=(const User& __x);
	bool operator == (const User& s) const { return socket_fd == s.socket_fd && nickname == s.nickname; }
	bool operator != (const User& s) const { return !operator==(s); }
	~User();

	void setNickname(const string &nickname);
	void setAutoReply(const string &autoReply);

	int getSocketFd() const;
	const string &getNickname() const;
	const string &getAutoReply() const;
};