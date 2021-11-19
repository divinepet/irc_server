#pragma once

#include "../server/Server.hpp"
#include "../models/Bot.hpp"

class Channel;
class User;
using namespace std;

class CommandList {
public:
	static void	adminCmd(vector<string> args, User& user);
	static void awayCmd(vector<string> args, User& user);
	static void infoCmd(vector<string> args, User& user);
	static void inviteCmd(vector<string> args, User& user);
	static void isonCmd(vector<string> args, User& user);
	static void joinCmd(vector<string> args, User& user);
	static void kickCmd(vector<string> args, User& user);
	static void killCmd(vector<string> args, User& user);
	static void	listCmd(vector<string> args, User& user);
	static void modeCmd(vector<string> args, User &user);
	static void motd(User& user);
	static void	namesCmd(vector<string> args, User& user);
	static int nickCmd(vector<string> args, User& user);
	static void noticeCmd(vector<string> args, User& user);
	static void operCmd(vector<string> args, User& user);
	static void partCmd(vector<string> args, User& user);
	static void passCmd(vector<string> args, User& user, string pass);
	static int pingCmd(vector<string> args, User& user);
	static int pongCmd(vector<string> args, User& user);
	static void privmsgCmd(vector<string> args, User& user, bool isNotice);
	static void quitCmd(User& user);
	static int restartCmd(User& user);
	static void rehashCmd(User& user);
	static void timeCmd(vector<string> args, User& user);
	static void topicCmd(vector<string> args, User &user);
    static bool checkModeParams(vector<string> args, User &user);
    static void setChnlMode(vector<string> args, User &user, Channel &chnl);
    static void setUserMode(vector<string> args, User &user);
    static void setChnlModeOperator(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModePrivate(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeSecret(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeInvite(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeTopic(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeOutside(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeModerated(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeLimit(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeBan(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeVoice(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setChnlModeKey(vector<string> args, User &user, Channel &rqsted_chnl);
    static void setUserModeInvisible(vector<string> args, User &user);
    static void setUserModeNoticed(vector<string> args, User &user);
    static void setUserModeWallops(vector<string> args, User &user);
    static void setUserModeOperator(vector<string> args, User &user);
	static int userCmd(vector<string> args, User& user);
	static void versionCmd(vector<string> args, User& user);
	static void wallopsCmd(vector<string> args, User& user);
	static void whoCmd(vector<string> args, User& user);
	static void whoWasCmd(vector<string> args, User& user);
	static void	whoisCmd(vector<string> args, User& user);

private:
	static void	getWildcardNickname(string str, User &user, list<User> &userlist);
	static void	getWildcardServerName(string str, User &user, list<User> &userlist);
	static void	getWildcardRealName(string str, User &user, list<User> &userlist);
	static void	getWildcardChannelName(string str, User &user, list<User> &userlist);
	static void	getWildcardHostName(string str, User &user, list<User> &userlist);
	static vector<string> getWhoReplyVector(User &user);
	static string getJoinedChannelsString(User &user, User &initiator);
	static string channelFlags(Channel &channel);
};
