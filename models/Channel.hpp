#pragma once

#include <iostream>
#include "../server/Server.hpp"

using namespace std;

class Channel {

public:
	Channel();

	Channel(std::string name) {
        _channel_name = name;
        _topic = "";
	}

	Channel(std::string name, User &user) {
	    _channel_name = name;
	    _user_list.push_back(user);
        _topic = "";
	};

	Channel(std::string name, User &user, std::string password) {
	    _channel_name = name;
	    _user_list.push_back(user);
	    _has_password = true;
	    _password = password;
	    _user_list.push_back(user);
        _topic = "";
	};

	virtual ~Channel();

	bool            _is_invite_only;
	bool            _has_password;
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

    string getChannelName() const;
    string getChannelTopic() const;


	bool operator == (const Channel& s) const { return _channel_name == s._channel_name; }

};

//bool operator==(const Channel& ch1, const Channel& ch2) {
//    return ch1.channel_name == ch2.channel_name;
//}
