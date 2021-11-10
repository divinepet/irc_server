#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MessageParse {
	vector<string> args;
public:
	MessageParse();
	virtual ~MessageParse();

	void splitMessage(char *__buf);
	void handleMessage(char *__buf);
	int defineCommandType();
	vector<string> getArgs() const;
};