#include "Bot.hpp"

Bot::Bot() {}

Bot::~Bot() {}

char Bot::asciitolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

void Bot::generateAnswer(User &user, string msg, const string& cmd, const string& ch_name ) {
	std::transform(msg.begin(), msg.end(), msg.begin(), asciitolower);
	if (msg.find("bot") == np)
		return;
	string prompt = ":BOT!PSINA@* :";

	string answer =
			(f("hi") || f("hello"))
			? prompt + "Hello, " + user.getNickname() + "! How are you?\n" :
			(f("fuck") || f("asshole"))
			? prompt + "Next time i will kick you...\n" : 0;


	send(user.getSocketFd(), answer.c_str(), answer.length(), 0 );
}
