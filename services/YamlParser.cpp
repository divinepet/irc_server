#include "YamlParser.hpp"

YamlParser::YamlParser() {
	loadFile();
}

YamlParser::~YamlParser() {}

void YamlParser::loadFile() {
	file.open ("resources/config.yaml", ifstream::in);
	vector<string> total_vec;
	string total_line = "";
	string line;
	size_t space_count = 0;
	size_t last_space_count = 0;

	while (getline(file, line)) {
		if (line.front() == ' ') {
			space_count = 0;
			while (line.front() == ' ') {
				space_count++;
				line.erase(0, 2);
			}
			if (space_count < last_space_count) {
				while (space_count < last_space_count) {
					if (total_vec.size() > 0)
						total_vec.pop_back();
					last_space_count--;
				}
			}
			last_space_count = space_count;
		} else {
			total_vec.clear();
			last_space_count = 0;
		}
		if (line.back() == ':') {
			total_vec.push_back(line.substr(0, line.length() - 1) + ".");
		}
		else {
			total_line.clear();
			for (vector<string>::iterator it = total_vec.begin(); it != total_vec.end(); ++it) {
				total_line += *it;
			}
			mapConfig.insert(make_pair(total_line + line.substr(0, line.find(':')), line.substr(line.find(':') + 2)));
//			cout << "total line: " << total_line << "$" << endl;
//			cout << total_line + line.substr(0, line.find(':')) << endl;
//			cout << line.substr(line.find(':') + 2) << endl;
		}
	}
}

string YamlParser::operator [](string const& name) {
	return mapConfig.find(name)->second;
}

string const YamlParser::operator [](string const& name) const {
	return mapConfig.find(name)->second;
}

