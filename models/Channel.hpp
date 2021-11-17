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
        _voice = false;
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
        _voice = false;
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
        _voice = false;
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
    bool            _banned;
    bool            _topic_by_oper;
    bool 			_voice;

    unsigned int    _user_limit;

    string          _topic;
	string          _password;
	string          _channel_name;
	list<User>      _userList;
	list<User>      _operator_list;
    list<User>      _invite_list;
    list<User>      _voice_list;
    list<User>      _ban_list;

	bool addUser(User &user);
    bool addUser(User &user, string password);
    void addUserToBanList(User &user);
    void addUserToInviteList(User &user);
    void addUserToVoiceList(User &user);
    void addOperator(User &user);
    void deleteUser(User &user);
    void deleteOperator(User &user);
    void sendToAll(User &sender, string channelName, string msg);

    bool                    isInviteOnly() const;
    bool                    isPassword() const;
    bool                    isOperator(User &user) const;
    bool 					inChannel(User user); // check that user in a channel
    bool                    isUserBanned(User &user);
    bool                    isUserInvited(User &user);
    bool                    isUserHasVoice(User &user);
    string                  getChannelName() const;
    string                  getChannelTopic() const;
    list<User>&             getBanList();
    list<User>&             getOperList();
    list<User>&				getUserList();
    list<User>&				getInviteList();
    list<User>&				getVoiceList();

    void setPrivateFlag(bool value);
    void setSecretFlag(bool value);
    void setInviteFlag(bool value);
    void setTopicFlag(bool value);
    void setOutsideFlag(bool value);
    void setModeratedFlag(bool value);
    void setUserLimit(unsigned int value);
    void setPassword(string pass);
    void resetPassword();


	bool operator == (const Channel& s) const { return _channel_name == s._channel_name; }

};

//bool operator==(const Channel& ch1, const Channel& ch2) {
//    return ch1.channel_name == ch2.channel_name;
//}
