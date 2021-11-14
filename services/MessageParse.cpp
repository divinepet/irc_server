#include "MessageParse.hpp"

bool bothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void MessageParse::splitMessage(string _msg, vector<string> &args) {
	_msg = _msg.substr(0, _msg.length() - 1);
	string delimiter = " ";
	size_t pos;
	string prefix;

	string::iterator new_end = unique(_msg.begin(), _msg.end(), bothAreSpaces);
	_msg.erase(new_end, _msg.end());
	if (_msg.size() > 0 && _msg[0] == ' ') _msg.erase(_msg.begin());
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

int MessageParse::defineCommandType(vector<string> &args, User& user, list<User>& users_list, string pass, list<Channel> &channel_list) {
	if (args[0] == "PASS") { /*CommandList::pass(args, user, users_list, pass);*/ }
	else if (args[0] == "NICK") { CommandList::nick(args, user, users_list); }
	else if (args[0] == "USER") { /*CommandList::user(args, user);*/ }
	else if (!user.isRegistered()) { Service::errMsg(451, user); }
	else if (args[0] == "ADMIN") { CommandList::admin(args, user); }
	else if (args[0] == "AWAY") { CommandList::away(args, user); }
	else if (args[0] == "JOIN") { CommandList::join(args, user, channel_list); }
	else if (args[0] == "INFO") { CommandList::info(args, user); }
	else if (args[0] == "INVITE") {}
	else if (args[0] == "ISON") { CommandList::ison(args, user, users_list); }
	else if (args[0] == "KICK") { CommandList::kick(args, user, channel_list); }
	else if (args[0] == "KILL") { CommandList::kill(args, user, users_list); }
	else if (args[0] == "LIST") { CommandList::list_cmd(args, user, channel_list); }
	else if (args[0] == "MODE") {}
	else if (args[0] == "NAMES") {}
	else if (args[0] == "NOTICE") {}
	else if (args[0] == "OPER") { CommandList::oper(args, user); }
	else if (args[0] == "PART") { CommandList::part(args, user, channel_list); }
	else if (args[0] == "PING") {}
	else if (args[0] == "PONG") {}
	else if (args[0] == "PRIVMSG") {}
	else if (args[0] == "QUIT") {}
	else if (args[0] == "REHASH") {}
	else if (args[0] == "RESTART") { return CommandList::restart(user); }
	else if (args[0] == "TIME") { CommandList::time(args, user); }
	else if (args[0] == "TOPIC") {}
	else if (args[0] == "VERSION") { CommandList::version(args, user); }
	else if (args[0] == "WALLOPS") {}
	else if (args[0] == "WHO") {}
	else if (args[0] == "WHOIS") {}
	else if (args[0] == "WHOWAS") {}
//	else if (args[0] == "USERS") {}
	else Service::errMsg(421, user, args[0]);
	return 0;
}

int MessageParse::handleMessage(string _msg, User& user, list<User>& users_list, string pass, list<Channel> &channel_list) {
	vector<string> args;

	splitMessage(_msg, args);
	return defineCommandType(args, user, users_list, pass, channel_list);

}
