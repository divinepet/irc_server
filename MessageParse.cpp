#include "MessageParse.hpp"

MessageParse::MessageParse() {}

MessageParse::~MessageParse() {}

void MessageParse::splitMessage(char *__buf) {
	string buf = "scott tiger  mushroom";
	string delimiter = " ";
	size_t pos = buf.find(delimiter);
	vector<string> args;
	string command = "";

	if (pos != string::npos) {
		command = buf.substr(0, pos);
		buf.erase(0, pos + delimiter.length());
	}

	cout << "command: " << command << endl;



	while ((pos = buf.find(delimiter)) != std::string::npos) {
		args.push_back(buf.substr(0, pos));
		buf.erase(0, pos + delimiter.length());
	}
	args.push_back(buf);

	for (vector<string>::iterator it = args.begin();  it != args.end(); ++it) {
		cout << *it << endl;
	}
}
