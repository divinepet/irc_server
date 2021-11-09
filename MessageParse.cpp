#include "MessageParse.hpp"

MessageParse::MessageParse() {}

MessageParse::~MessageParse() {}

bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }

void MessageParse::splitMessage(char *__buf) {
	string buf = __buf;
	string delimiter = " ";
	vector<string> args;
	size_t pos;

	// removing duplicate spaces in buffer
	string::iterator new_end = unique(buf.begin(), buf.end(), BothAreSpaces);
	buf.erase(new_end, buf.end());
	if (buf[0] == ' ') buf.erase(buf.begin());


	// pushing all words in vector
	while ((pos = buf.find(delimiter)) != std::string::npos) {
		args.push_back(buf.substr(0, pos));
		buf.erase(0, pos + delimiter.length());
	}
	args.push_back(buf);

	for (vector<string>::iterator it = args.begin();  it != args.end(); ++it) {
		cout << *it << endl;
	}
}
