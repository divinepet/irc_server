#include "YamlParser.hpp"

YamlParser::YamlParser() {}

YamlParser::~YamlParser() {}

std::ostream &operator<<(std::ostream &out, YamlParser const &other) {
	return out << "Class visability";
}
