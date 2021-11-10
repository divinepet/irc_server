#include "MessageParse.hpp"

bool bothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
bool bothAreNewLines(char lhs, char rhs) { return (lhs == rhs) && (lhs == '\n'); }

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

	printf("command: %s, ", args[0].c_str());
	printf("args:");

	for (vector<string>::iterator it = args.begin();  it != args.end(); ++it) {
		printf(" [%s]", (*it).c_str());
	}
	cout << endl;
}

int MessageParse::defineCommandType(vector<string> &args, User& user) {
	if (!args.size()) return -1;
	else if (args[0] == "ADMIN") {
		CommandList::admin(args, user);
		return 1;
	}
	else if (args[0] == "AWAY") return 2;
	else if (args[0] == "INFO") return 3;
	else if (args[0] == "INVITE") return 4;
	else if (args[0] == "ISON") return 5;
	else if (args[0] == "JOIN") return 6;
	else if (args[0] == "KICK") return 7;
	else if (args[0] == "KILL") return 8;
	else if (args[0] == "LIST") return 9;
	else if (args[0] == "MODE") return 10;
	else if (args[0] == "NAMES") return 11;
	else if (args[0] == "NICK") return 12;
	else if (args[0] == "NOTICE") return 13;
	else if (args[0] == "OPER") return 14;
	else if (args[0] == "PART") return 15;
	else if (args[0] == "PASS") return 16;
	else if (args[0] == "PING") return 17;
	else if (args[0] == "PONG") return 18;
	else if (args[0] == "PRIVMSG") return 19;
	else if (args[0] == "QUIT") return 20;
	else if (args[0] == "REHASH") return 21;
	else if (args[0] == "RESTART") return 22;
	else if (args[0] == "TIME") return 23;
	else if (args[0] == "TOPIC") return 24;
	else if (args[0] == "USER") return 25;
	else if (args[0] == "VERSION") return 26;
	else if (args[0] == "WALLOPS") return 27;
	else if (args[0] == "WHO") return 28;
	else if (args[0] == "WHOIS") return 29;
	else if (args[0] == "WHOWAS") return 30;
//	else if (args[0] == "USERS") return 31;
	return -1;
}


void MessageParse::handleMessage(char *__buf, User& user) {
	vector<string> args;

	splitMessage(__buf, args);
	if (defineCommandType(args, user) == -1)
		printf("command not found\n");
}
