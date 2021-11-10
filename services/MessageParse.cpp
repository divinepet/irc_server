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

int MessageParse::defineCommandType(vector<string> &args, User& user) {
	if (!args.size()) return -1;
	else if (args[0] == "ADMIN") { return CommandList::admin(args, user); }
	else if (args[0] == "AWAY") return 1;
	else if (args[0] == "INFO") return 1;
	else if (args[0] == "INVITE") return 1;
	else if (args[0] == "ISON") return 1;
	else if (args[0] == "JOIN") return 1;
	else if (args[0] == "KICK") return 1;
	else if (args[0] == "KILL") return 1;
	else if (args[0] == "LIST") return 1;
	else if (args[0] == "MODE") return 1;
	else if (args[0] == "NAMES") return 1;
	else if (args[0] == "NICK") return 1;
	else if (args[0] == "NOTICE") return 1;
	else if (args[0] == "OPER") return 1;
	else if (args[0] == "PART") return 1;
	else if (args[0] == "PASS") return 1;
	else if (args[0] == "PING") return 1;
	else if (args[0] == "PONG") return 1;
	else if (args[0] == "PRIVMSG") return 1;
	else if (args[0] == "QUIT") return 1;
	else if (args[0] == "REHASH") return 1;
	else if (args[0] == "RESTART") return 1;
	else if (args[0] == "TIME") return 1;
	else if (args[0] == "TOPIC") return 1;
	else if (args[0] == "USER") return 1;
	else if (args[0] == "VERSION") return 1;
	else if (args[0] == "WALLOPS") return 1;
	else if (args[0] == "WHO") return 1;
	else if (args[0] == "WHOIS") return 1;
	else if (args[0] == "WHOWAS") return 1;
//	else if (args[0] == "USERS") return 1;
	return -1;
}

void MessageParse::handleMessage(char *__buf, User& user) {
	vector<string> args;

	splitMessage(__buf, args);
	if (defineCommandType(args, user) == -1)
		Server::writing(user.getSocketFd(), "command not found\n");
}
