#include "MessageParse.hpp"

bool bothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void MessageParse::splitMessage(string _msg, vector<string> &args) {
	string delimiter = " ";
	size_t pos;
	string prefix;

	string::iterator new_end = unique(_msg.begin(), _msg.end(), bothAreSpaces);
	_msg.erase(new_end, _msg.end());
	if (!_msg.empty() && _msg[0] == ' ') _msg.erase(_msg.begin());
	if (_msg[_msg.size() - 1] == ' ') _msg.erase(_msg.end() - 1);


	while ((pos = _msg.find(delimiter)) != std::string::npos) {
		args.push_back(_msg.substr(0, pos));
		_msg.erase(0, pos + delimiter.length());
	}
	args.push_back(_msg);

	size_t i = 0;
	for (vector<string>::iterator it = args.begin();  it != args.end(); ++it, ++i) {
		if ((*it).front() == ':' && i == 0) {
			(*it).erase(0, 1);
			prefix = *it;
			args.erase(it);
		}
		else if ((*it).front() == ':') {
			(*it).erase(0, 1);
			vector<string>::iterator it2 = it + 1;
			vector<string>::iterator it3 = it + 1;
			for (;  it2 != args.end(); ++it2)
				*it = *it + " " + *it2;
			args.erase(it3, args.end());
		}
	}

	printf("prefix: <%s>, ", prefix.c_str());
	printf("command: <%s>, ", args[0].c_str());
	printf("%lu args:", args.size() - 1);
	for (vector<string>::iterator it = args.begin() + 1;  it != args.end(); ++it)
		printf(" (%s)", (*it).c_str());
	cout << endl;
}

int MessageParse::defineCommandType(vector<string> &args, User& user, string pass, int socket) {
	if (args[0] == "PASS") { CommandList::passCmd(args, user, pass); }
	else if (args[0] == "NICK") { return CommandList::nickCmd(args, user); }
	else if (args[0] == "USER") { return CommandList::userCmd(args, user); }
	else if (args[0] == "QUIT") { CommandList::quitCmd(user); }
	else if (!user.isRegistered()) { Service::errMsg(451, user); }
	else if (args[0] == "ADMIN") { CommandList::adminCmd(args, user); }
	else if (args[0] == "AWAY") { CommandList::awayCmd(args, user); }
	else if (args[0] == "JOIN") { CommandList::joinCmd(args, user); }
	else if (args[0] == "INFO") { CommandList::infoCmd(args, user); }
	else if (args[0] == "INVITE") { CommandList::inviteCmd(args, user); }
	else if (args[0] == "ISON") { CommandList::isonCmd(args, user); }
	else if (args[0] == "KICK") { CommandList::kickCmd(args, user); }
	else if (args[0] == "KILL") { CommandList::killCmd(args, user); }
	else if (args[0] == "LIST") { CommandList::listCmd(args, user); }
	else if (args[0] == "MODE") { CommandList::modeCmd(args, user); }
	else if (args[0] == "NAMES") {CommandList::namesCmd(args, user); }
	else if (args[0] == "NOTICE") { CommandList::noticeCmd(args, user); }
	else if (args[0] == "OPER") { CommandList::operCmd(args, user); }
	else if (args[0] == "PART") { CommandList::partCmd(args, user); }
	else if (args[0] == "PING") { return CommandList::pingCmd(args, user); }
	else if (args[0] == "PONG") { return CommandList::pongCmd(args, user); }
	else if (args[0] == "PRIVMSG") { CommandList::privmsgCmd(args, user, false); }
	else if (args[0] == "REHASH") { CommandList::rehashCmd(user); }
	else if (args[0] == "RESTART") { return CommandList::restartCmd(user); }
	else if (args[0] == "TIME") { CommandList::timeCmd(args, user); }
	else if (args[0] == "TOPIC") { CommandList::topicCmd(args, user); }
	else if (args[0] == "VERSION") { CommandList::versionCmd(args, user); }
	else if (args[0] == "WALLOPS") { CommandList::wallopsCmd(args, user); }
	else if (args[0] == "WHO") { CommandList::whoCmd(args, user); }
	else if (args[0] == "WHOIS") { CommandList::whoisCmd(args, user); }
	else if (args[0] == "WHOWAS") { CommandList::whoWasCmd(args, user); }
	else Service::errMsg(421, user, args[0]);
	return 0;
}

int MessageParse::handleMessage(string _msg, User& user, int socket, string pass) {
	if (_msg == "\n") return 0;
	vector<string> args;

	splitMessage(_msg, args);
	return defineCommandType(args, user, pass, socket);

}
