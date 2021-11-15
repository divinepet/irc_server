#pragma once
#ifndef YAML_PARSER_HPP
#define YAML_PARSER_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class YamlParser {
	std::ifstream file;
	map<string, string> mapConfig;
public:
	YamlParser();
	virtual ~YamlParser();
	void loadFile();
	void reload();
	string operator [](string const& name);
	string const operator [](string const& name) const;
};

#endif