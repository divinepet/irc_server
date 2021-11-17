#include "Service.hpp"

time_t Service::timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

string Service::getDate() {
	time_t timetoday;
	time(&timetoday);
	string result = asctime(localtime(&timetoday));
	return result.substr(0, result.length() - 1);
}

// not full-tested

bool Service::isComma(char c) { return c == ','; }

bool Service::isNotComma(char c) { return c != ','; }

vector<string>	Service::split(const std::string& s, char c) {
    typedef std::string::const_iterator iter;
    std::vector<std::string> ret;
    iter i = s.begin();
    while(i!=s.end()) {
        i = std::find_if(i, s.end(), isNotComma); // find the beginning of a word
        iter j= std::find_if(i, s.end(), isComma); // find the end of the same word
        if(i!=s.end()){
            ret.push_back(std::string(i, j)); //insert the word into vector
            i = j; // repeat 1,2,3 on the rest of the line.
        }
    }
    return ret;
}

void Service::errMsg(int err, User &user, string arg1, string arg2) {
	string msg = ":" + config["server.name"] + " " + std::to_string(err) + " " + user.getNickname();
	switch (err) {
		case 401: msg += " " + arg1 + " :No such nick/channel\n"; break;
		case 402: msg += " " + arg1 + " :No such server\n"; break;
		case 403: msg += " " + arg1 + " :No such channel\n"; break;
		case 404: msg += " " + arg1 + " :Cannot send to channel\n"; break;
		case 405: msg += " " + arg1 + " :You have joined too many channels\n"; break;
		case 406: msg += " " + arg1 + " :There was no such nickname\n"; break;
		case 407: msg += " " + arg1 + " :Duplicate recipients. No arg1 delivered\n"; break;
		case 409: msg += " :No origin specified\n"; break;
		case 411: msg += " :No recipient given (" + arg1 + ")\n"; break;
		case 412: msg += " :No text to send\n"; break;
		case 413: msg += " " + arg1 + " :No toplevel domain specified\n"; break;
		case 414: msg += " " + arg1 + " :Wildcard in toplevel domain\n"; break;
		case 421: msg += " " + arg1 + " :Unknown command\n"; break;
		case 422: msg += " :MOTD File is missing\n"; break;
		case 423: msg += " " + arg1 + " :No administrative info available\n"; break;
		case 424: msg += " :File error doing \n" + arg1 + " on " + arg2 + "\n"; break;
		case 431: msg += " :No nickname given\n"; break;
		case 432: msg += " " + arg1 + " :Erroneus nickname\n"; break;
		case 433: msg += " " + arg1 + " :Nickname is already in use\n"; break;
		case 436: msg += " " + arg1 + " :Nickname collision KILL\n"; break;
		case 441: msg += " " + arg1 + " " + arg2 + " :They aren't on that channel\n"; break;
		case 442: msg += " " + arg1 + " :You're not on that channel\n"; break;
		case 443: msg += " " + arg1 + " " + arg2 + " :is already on channel\n"; break;
		case 444: msg += " " + arg1 + " :User not logged in\n"; break;
		case 445: msg += " :SUMMON has been disabled\n"; break;
		case 446: msg += " :USERS has been disabled\n"; break;
		case 451: msg += " :You have not registered\n"; break;
		case 461: msg += " " + arg1 + " :Not enough parameters\n"; break;
		case 462: msg += " :You may not reregister\n"; break;
		case 463: msg += " :Your host isn't among the privileged\n"; break;
		case 464: msg += " :Password incorrect\n"; break;
		case 465: msg += " :You are banned from this server\n"; break;
		case 467: msg += " " + arg1 + " :Channel key already set\n"; break;
		case 471: msg += " " + arg1 + " :Cannot join channel (+l)\n"; break;
		case 472: msg += " " + arg1 + " :is unknown mode char to me\n"; break;
		case 473: msg += " " + arg1 + " :Cannot join channel (+i)\n"; break;
		case 474: msg += " " + arg1 + " :Cannot join channel (+b)\n"; break;
		case 475: msg += " " + arg1 + " :Cannot join channel (+k)\n"; break;
		case 481: msg += " :Permission Denied- You're not an IRC operator\n"; break;
		case 482: msg += " " + arg1 + " :You're not channel operator\n"; break;
		case 483: msg += " :You cant kill a server!\n"; break;
		case 491: msg += " :No O-lines for your host\n"; break;
		case 501: msg += " :Unknown MODE flag\n"; break;
		case 502: msg += " :Cant change mode for other users\n"; break;
		default: msg += "UNKNOWN ERROR\n"; break;
	}
	Server::writing(user.getSocketFd(), msg);
}

void Service::replyMsg(int code, User &user, string arg1, string arg2, string arg3, string arg4,
									string arg5, string arg6, string arg7, string arg8) {
	string msg = ":" + config["server.name"] + " " + std::to_string(code) + " " + user.getNickname() + " ";
	switch (code) {
		case 302: msg += ":" + arg1 + "\n"; break;
		case 303: msg += ":" + arg1 + "\n"; break;
		case 301: msg += arg1 + " :" + arg2 + "\n"; break;
		case 305: msg += ":You are no longer marked as being away\n"; break;
		case 306: msg += ":You have been marked as being away\n"; break;
		case 311: msg += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n"; break;
		case 312: msg += arg1 + " " + arg2 + " :" + arg3 + "\n"; break;
		case 313: msg += arg1 + " :is an IRC operator\n"; break;
		case 317: msg += arg1 + " " + arg2 + " " + arg3 + " :seconds idle\n"; break;
		case 318: msg += arg1 + " :End of /WHOIS list\n"; break;
		case 319: msg += arg1 + " :" + arg2 + "\n"; break;
		case 314: msg += arg1 + " " + arg2 + " " + arg3 + " * :" + arg4 + "\n"; break;
		case 369: msg += arg1 + " :End of WHOWAS\n"; break;
		case 321: msg += "Channel :Users  Name\n"; break;
		case 322: msg += arg1 + " " + arg2 + " :" + arg3 + "\n"; break;
		case 323: msg += ":End of /LIST\n"; break;
		case 324: msg += arg1 + " +" + arg2 + "\n"; break;
		case 331: msg += arg1 + " :No topic is set\n"; break;
		case 332: msg += arg1 + " :" + arg2 + "\n"; break;
		case 341: msg += arg1 + " " + arg2 + "\n"; break;
		case 342: msg += arg1 + " :Summoning user to IRC\n"; break;
		case 351: msg += arg1 + "." + arg2 + " " + arg3 + " :" + arg4 + "\n"; break;
		case 352: msg += arg1 + " " + arg2 + " " + arg3 + " " + arg4 + " ";
				  msg += arg5 + " " + arg6 + " :" + arg7 + " " + arg8 + "\n"; break;
		case 315: msg += arg1 + " :End of /WHO list\n"; break;
		case 353: msg += arg1 + " :" + arg2 + "\n"; break;
		case 366: msg += arg1 + " :End of /NAMES list\n"; break;
		case 364: msg += arg1 + " " + arg2 + ": " + arg3 + " " + arg4 + "\n"; break;
		case 365: msg += arg1 + " :End of /LINKS list\n"; break;
		case 367: msg += arg1 + " " + arg2 + "\n"; break;
		case 368: msg += arg1 + " :End of channel ban list\n"; break;
		case 371: msg += ":" + arg1 + "\n"; break;
		case 374: msg += ":End of /INFO list\n"; break;
		case 375: msg += ":- " + arg1 + " Message of the day - \n"; break;
		case 372: msg += ":- " + arg1 + "\n"; break;
		case 376: msg += ":End of /MOTD command\n"; break;
		case 381: msg += ":You are now an IRC operator\n"; break;
		case 382: msg += arg1 + " :Rehashing\n"; break;
		case 391: msg += arg1 + " :" + arg2 + "\n"; break;
		case 392: msg += ":UserID   Terminal  Host\n"; break;
		case 393: msg += ":%-8s %-9s %-8s\n"; break; // строка длиной 8 символов
		case 394: msg += ":End of users\n"; break;
		case 395: msg += ":Nobody logged in\n"; break;
		case 200: msg += "Link " + arg1 + " " + arg2 + " " + arg3 + "\n"; break;
		case 201: msg += "Try. " + arg1 + " " + arg2 + "\n"; break;
		case 202: msg += "H.S. " + arg1 + " " + arg2 + "\n"; break;
		case 203: msg += "???? " + arg1 + " " + arg2 + "\n"; break;
		case 204: msg += "Oper " + arg1 + " " + arg2 + "\n"; break;
		case 205: msg += "User " + arg1 + " " + arg2 + "\n"; break;
		case 206: msg += "Serv " + arg1 + " " + arg2 + "S " + arg3 + "C ";
				  msg += arg4 + " " + arg5 + "@" + arg6 + "\n"; break;
		case 208: msg += arg1 + " 0 " + arg2 + "\n"; break;
		case 261: msg += "File " + arg1 + " " + arg2 + "\n"; break;
		case 211: msg += arg1 + " " + arg2 + " " + arg3 + " " + arg4 + " ";
				  msg += arg5 + " " + arg6 + " " + arg7 + "\n"; break;
		case 212: msg += arg1 + " " + arg2 + "\n"; break;
		case 213: msg += "C " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 214: msg += "N " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 215: msg += "I " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 216: msg += "K " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 218: msg += "Y " + arg1 + " * " + arg2 + " " + arg3 + " " + arg4 + "\n"; break;
		case 219: msg += arg1 + " :End of /STATS report\n"; break;
		case 241: msg += "L " + arg1 + " * " + arg2 + " " + arg3 + "\n"; break;
		case 242: msg += ":Server Up %d days %d:%02d:%02d\n"; break;
		case 243: msg += "O " + arg1 + " * " + arg2 + "\n"; break;
		case 244: msg += "H " + arg1 + " * " + arg2 + "\n"; break;
		case 221: msg += arg1 + "\n"; break;
		case 251: msg += ":There are " + arg1 + " users and " + arg2;
				  msg += " invisible on " + arg3 + " servers\n"; break;
		case 252: msg += arg1 + " :operator(s) online\n"; break;
		case 253: msg += arg1 + " :unknown connection(s)\n"; break;
		case 254: msg += arg1 + " :channels formed\n"; break;
		case 255: msg += ":I have " + arg1 + " clients and " + arg2 + " servers\n"; break;
		case 256: msg += arg1 + " :Administrative info\n"; break;
		case 257: msg += ":Name     " + arg1 + "\n"; break;
		case 258: msg += ":Nickname " + arg1 + "\n"; break;
		case 259: msg += ":E-Mail   " + arg1 + "\n"; break;
		default: msg += "UNKNOWN REPLY\n"; break;
	}
	Server::writing(user.getSocketFd(), msg);
}

void Service::sendMsg(int code, User &sender, User& recipient, string arg1, string arg2, string arg3, string arg4) {
	string msg = ":" + sender.getNickname() + "!" + sender.getUsername() + "@" + sender.getRealHost() + " ";
	switch (code) {
		case 1: msg += arg1 + " " + arg2 + " :" + arg3 + "\n"; break;
		case 2: msg += arg1 + " :" + arg2 + "\n"; break;
	}
	Server::writing(recipient.getSocketFd(), msg);
}

bool Service::channelIsEmpty(const Channel &channel) {
	return (channel._userList.size() == 0);
}

bool Service::isChannelName(string str) {

    for (size_t i = 0; i < str.length(); i++) {
        if (i == 0 && (str[i] != '#' && str[i] != '&'))
            return false;
        else if (str[i] == ' ' || str[i] == 7 || str[i] == ',')
            return false;
    }
    return true;
}

pair<list<User>::iterator, bool> Service::isUserExist(string name) {
	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); ++it)
    	if (it->getNickname() == name) return make_pair(it, true);
	return make_pair(Server::userList.end(),true);
}

pair<list<Channel>::iterator, bool> Service::isChannelExist(string name) {
	for (list<Channel>::iterator it = Server::channelList.begin(); it != Server::channelList.end(); ++it)
		if (it->getChannelName() == name) return make_pair(it, true);
	return make_pair(Server::channelList.end(), false);
}

pair<list<Channel>::iterator, bool> Service::isChannelExist(list<Channel> &channelList, string name) {
	for (list<Channel>::iterator it = channelList.begin(); it != channelList.end(); ++it)
		if (it->getChannelName() == name)
			return make_pair(it, true);
		return make_pair(channelList.end(), false);
}

pair<list<User>::iterator, bool> Service::isUserExist(list<User> &usersList, string name) {
	for (list<User>::iterator it = usersList.begin(); it != usersList.end(); ++it)
    	if (it->getNickname() == name)
			return make_pair(it, true);
    return make_pair(usersList.end(), false);
}


string	Service::getUsersFromList(User &user, list<User> &userlist) {

	std::string result = "";
	for (list<User>::iterator it = userlist.begin(); it != userlist.end(); ++it) {
		if (Service::isUserExist(it->getNickname()).first->isInvisible() && user.getNickname() == it->getNickname()) {
			result += it->getNickname();
			result += " ";
		} else if (!Service::isUserExist(it->getNickname()).first->isInvisible()) {
			result += it->getNickname();
			result += " ";
		}
	}
	return result;
}

void	Service::deleteChannelFromUser(User &user, Channel &channel) {
	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); it++) {
		if (user.getNickname() == it->getNickname()) {
			it->joinedChannels.remove(channel);
		}
	}
}

void Service::sendFile(User &sender, string &recipient, const string& fileName) {
	for (list<User>::iterator it = Server::userList.begin(); it != Server::userList.end(); ++it) {
		if (it->getNickname() == recipient) {
			fstream file;
			file.open(fileName, ios::in | ios::binary);

			if (file.is_open()) {
				string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
				send(it->getSocketFd() , contents.c_str() , contents.length() , 0);
			} else
				cout << "cant open file" << endl;
			file.close();
			break;
		} else {
			cout << "User not found" << endl;
		}
	}
}

string Service::to_string(list<User> lst, Channel &channel) {
	string result = "";
	for (list<User>::iterator it = lst.begin(); it != lst.end(); ++it) {
		if (it != lst.begin())
			result += " ";
		if (channel.isOperator(*it))
			continue;
		result += it->getNickname();
	}
	return result;
}

string Service::to_string(list<User> lst, bool isOperList) {
	string result = "";
	for (list<User>::iterator it = lst.begin(); it != lst.end(); ++it) {
		if (it != lst.begin())
			result += " ";
		if (isOperList)
			result += "@";
		result += it->getNickname();
	}
	return result;
}


// 0 JOIN
// 1 "#abc abc, sda asdf, as, fdas # afsfa"
