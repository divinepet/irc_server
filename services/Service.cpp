#include "Service.hpp"

string Service::getTime() {
	time_t result = time(NULL);
	string time_now = "[" + to_string(localtime(&result)->tm_hour) + ":" + to_string(localtime(&result)->tm_min) + ":" +
			to_string(localtime(&result)->tm_sec) + "]";
	return time_now;
}

string Service::formatMsg(int replyCode, const string msg, User &user) {
	return ":" + serverInfo::serverName + " " + to_string(replyCode) + " " + user.getNickname() + ": " + msg + "\n";
}

string Service::formatMsg(int replyCode, const string msg, User &user, string optional) {
	return ":" + serverInfo::serverName + " " + to_string(replyCode) + " " + user.getNickname() + " " + optional + ": " + msg + "\n";
}

