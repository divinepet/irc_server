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
	if (msg.find("bot") == string::npos)
		return;
	string prompt = ":BOT!PSINA@* :";

	string answer =
			f2("hi", "hello")
			? prompt + "Hello, " + user.getNickname() + "! How are you?\n" :
			f3("fuck", "asshole", "bitch")
			? prompt + "Next time i will kick you...\n" :
			f2("how", "are")
			? prompt + "I feel complete, as i've never felt before\n" :
			f1("time")
			? prompt + "Type TIME command to know the time.\n" :
			f1("bye")
			? prompt + "I'm looking forward to seeing you again!\n" :
			f2("command", "channel")
			? prompt + "Check RFC1459 protocol, they are too many\n" : "\n";

    Service::sendMsg(user, user, "PRIVMSG", ch_name, answer);
}
