#include "Bot.hpp"

Bot::Bot() {}

Bot::~Bot() {}

char Bot::asciitolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

void Bot::generateAnswer(User &user, string msg, const string& cmd, const string& ch_name ) {
	string prompt = ":BOT_PSINA!@* " + cmd + " " + ch_name + " :";
	std::transform(msg.begin(), msg.end(), msg.begin(), asciitolower);
	cout << msg << endl;
	if (msg.find("hi") != string::npos || msg.find("hello") != string::npos) {
		string answer = prompt + "Nice to meet you in channel, " + user.getNickname() + "!\n";
		send(user.getSocketFd(), answer.c_str(), answer.length(), 0 );
	} else if (msg.find("fuck")  != string::npos && msg.find("bot")  != string::npos) {
		string answer = prompt + "poshel ti nahui, " + user.getNickname() + "!\n";
		send(user.getSocketFd(), answer.c_str(), answer.length(), 0 );
	}
}
