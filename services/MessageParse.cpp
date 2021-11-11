#include "MessageParse.hpp"

bool bothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void MessageParse::splitMessage(char *__buf, vector<string> &args) {
	string buf = __buf;
	buf = buf.substr(0, buf.length() - 1);
	string delimiter = " ";
	size_t pos;

	// removing duplicate spaces in buffer
	string::iterator new_end = unique(buf.begin(), buf.end(), bothAreSpaces);
	buf.erase(new_end, buf.end());
	if (buf[0] == ' ') buf.erase(buf.begin());


	// split by space character and pushing all words in vector
	// first element is a command, other remaining are arguments
	while ((pos = buf.find(delimiter)) != std::string::npos) {
		args.push_back(buf.substr(0, pos));
		buf.erase(0, pos + delimiter.length());
	}
	args.push_back(buf);

	printf("command: <%s>, ", args[0].c_str());
	printf("%lu args:", args.size() - 1);

	for (vector<string>::iterator it = args.begin() + 1;  it != args.end(); ++it)
		printf(" [%s]", (*it).c_str());
	cout << endl;
}

void MessageParse::defineCommandType(vector<string> &args, User& user) {
	if (args[0] == "PASS") { }
	else if (args[0] == "NICK") { CommandList::nick(args, user); }
	else if (args[0] == "USER") { }
	else if (!user.isRegistered()) { Server::writing(user.getSocketFd(), Service::formatMsg(451, "You are not registered", user)); }
	else if (args[0] == "ADMIN") { CommandList::admin(args, user); }
	else if (args[0] == "AWAY") { CommandList::away(args, user); }
	else if (args[0] == "JOIN") {}
	else if (args[0] == "INFO") { CommandList::info(args, user); }
	else if (args[0] == "INVITE") {}
	else if (args[0] == "ISON") {}
	else if (args[0] == "KICK") {}
	else if (args[0] == "KILL") {}
	else if (args[0] == "LIST") {}
	else if (args[0] == "MODE") {}
	else if (args[0] == "NAMES") {}
	else if (args[0] == "NOTICE") {}
	else if (args[0] == "OPER") {}
	else if (args[0] == "PART") {}
	else if (args[0] == "PING") {}
	else if (args[0] == "PONG") {}
	else if (args[0] == "PRIVMSG") {}
	else if (args[0] == "QUIT") {}
	else if (args[0] == "REHASH") {}
	else if (args[0] == "RESTART") {}
	else if (args[0] == "TIME") {}
	else if (args[0] == "TOPIC") {}
	else if (args[0] == "VERSION") {}
	else if (args[0] == "WALLOPS") {}
	else if (args[0] == "WHO") {}
	else if (args[0] == "WHOIS") {}
	else if (args[0] == "WHOWAS") {}
//	else if (args[0] == "USERS") {}
	else Server::writing(user.getSocketFd(), Service::formatMsg(451, "command not found", user));
}

void MessageParse::handleMessage(char *__buf, User& user) {
	vector<string> args;

	splitMessage(__buf, args);
	defineCommandType(args, user);
}
