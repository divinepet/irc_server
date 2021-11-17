#pragma once

#include <iostream>
#include "../server/Server.hpp"

using namespace std;

class User;

class Channel {

public:
	Channel();

	Channel(std::string name) {
        _channel_name = name;
        _topic = "";
        _has_password = false;
        _invite_only = false;
        _secret = false;
        _private = false;
        _no_outside = false;
        _moderated = false;
        _voice = true;
        _banned = false;
        _topic_by_oper = false;
        _user_limit = 100;
    }

	Channel(std::string name, User &user) {
	    _channel_name = name;
	    _userList.push_back(user);
        _topic = "";
        _has_password = false;
        _invite_only = false;
        _secret = false;
        _private = false;
        _no_outside = false;
        _moderated = false;
        _voice = true;
        _banned = false;
        _topic_by_oper = false;
        _user_limit = 100;
	};

	Channel(std::string name, User &user, std::string password) {
	    _channel_name = name;
	    _userList.push_back(user);
	    _has_password = true;
	    _password = password;
	    _userList.push_back(user);
        _topic = "";
        _has_password = false;
        _invite_only = false;
        _secret = false;
        _private = false;
        _no_outside = false;
        _moderated = false;
        _voice = true;
        _banned = false;
        _topic_by_oper = false;
        _user_limit = 100;
	};

	virtual ~Channel();

	bool            _invite_only;
	bool            _has_password;
    bool            _secret;
    bool            _private;
    bool            _no_outside;
    bool            _moderated;
    bool            _voice;
    bool            _banned;
    bool            _topic_by_oper;

    unsigned int    _user_limit;

    string          _topic;
	string          _password;
	string          _channel_name;
	list<User>      _userList;
	list<User>      _operator_list;
    list<User>      _invite_list;
    list<string>    _ban_list;

	bool addUser(User &user);
    bool addUser(User &user, string password);
    void addOperator(User &user);
    void deleteUser(User &user);
    void deleteOperator(User &user);

    bool                    isInviteOnly() const;
    bool                    isPassword() const;
    bool                    isOperator(User &user) const;
    bool 					inChannel(User user); // check that user in a channel
    string                  getChannelName() const;
    string                  getChannelTopic() const;
    list<string>&           getBanList();
    list<User>&             getOperList();
    list<User>&				getUserList();

    void setPrivateFlag(bool value);
    void setSecretFlag(bool value);
    void setInviteFlag(bool value);
    void setTopicFlag(bool value);
    void setOutsideFlag(bool value);
    void setModeratedFlag(bool value);
    void setUserLimit(unsigned int value);
    void setVoiceFlag(bool value);
    void setPassword(string pass);


	bool operator == (const Channel& s) const { return _channel_name == s._channel_name; }

};

//bool operator==(const Channel& ch1, const Channel& ch2) {
//    return ch1.channel_name == ch2.channel_name;
//}
