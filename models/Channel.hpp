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
    }

	Channel(std::string name, User &user) {
	    _channel_name = name;
	    _user_list.push_back(user);
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
	};

	Channel(std::string name, User &user, std::string password) {
	    _channel_name = name;
	    _user_list.push_back(user);
	    _has_password = true;
	    _password = password;
	    _user_list.push_back(user);
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

    std::string     _topic;
	std::string     _password;
	std::string     _channel_name;
	std::list<User> _user_list;
	std::list<User> _operator_list;
    std::list<User> _invite_list;

	bool addUser(User &user);
    bool addUser(User &user, string password);
    void addOperator(User &user);
    void deleteUser(User &user);
    void deleteOperator(User &user);

    bool                    isInviteOnly() const;
    bool 					inChannel(User user); // check that user in a channel
    string                  getChannelName() const;
    string                  getChannelTopic() const;
    list<User>::iterator    getOperListBegin();
    list<User>::iterator    getOperListEnd();


	bool operator == (const Channel& s) const { return _channel_name == s._channel_name; }

};

//bool operator==(const Channel& ch1, const Channel& ch2) {
//    return ch1.channel_name == ch2.channel_name;
//}
