#include "MessageParse.hpp"

bool bothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void MessageParse::splitMessage(char *_buf, vector<string> &args) {
	string buf = _buf;
	buf = buf.substr(0, buf.length() - 1);
	string delimiter = " ";
	size_t pos;
	string prefix;

	string::iterator new_end = unique(buf.begin(), buf.end(), bothAreSpaces);
	buf.erase(new_end, buf.end());
	if (buf.size() > 0 && buf[0] == ' ') buf.erase(buf.begin());
	if (buf[buf.size() - 1] == ' ') buf.erase(buf.end() - 1);


	while ((pos = buf.find(delimiter)) != std::string::npos) {
		args.push_back(buf.substr(0, pos));
		buf.erase(0, pos + delimiter.length());
	}
	args.push_back(buf);

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

void MessageParse::defineCommandType(vector<string> &args, User& user, list<User>& users_list, string pass, list<Channel> &channel_list) {
	if (args[0] == "PASS") { /*CommandList::pass(args, user, users_list, pass);*/ }
	else if (args[0] == "NICK") { CommandList::nick(args, user); }
	else if (args[0] == "USER") { /*CommandList::user(args, user);*/ }
	else if (!user.isRegistered()) { Service::errMsg(451, user); }
	else if (args[0] == "ADMIN") { CommandList::admin(args, user); }
	else if (args[0] == "AWAY") { CommandList::away(args, user); }
	else if (args[0] == "JOIN") { CommandList::join(args, user, channel_list); }
	else if (args[0] == "INFO") { CommandList::info(args, user); }
	else if (args[0] == "INVITE") {}
	else if (args[0] == "ISON") { CommandList::ison(args, user, users_list); }
	else if (args[0] == "KICK") {}
	else if (args[0] == "KILL") {}
	else if (args[0] == "LIST") {}
	else if (args[0] == "MODE") {}
	else if (args[0] == "NAMES") {}
	else if (args[0] == "NOTICE") {}
	else if (args[0] == "OPER") {}
	else if (args[0] == "PART") { CommandList::part(args, user, channel_list); }
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
	else Service::errMsg(421, user, args[0]);
}

void MessageParse::handleMessage(char *_buf, User& user, list<User>& users_list, string pass, list<Channel> &channel_list) {
	vector<string> args;

	splitMessage(_buf, args);
	defineCommandType(args, user, users_list, pass, channel_list);
}
