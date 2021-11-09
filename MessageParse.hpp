#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MessageParse {
public:
	MessageParse();
	virtual ~MessageParse();

	void splitMessage(char *__buf);
};