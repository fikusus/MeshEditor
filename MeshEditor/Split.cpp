#include "Split.h"

const std::string& Split::getName() const {

	return name;
}

int Split::execute(const std::map<std::string, std::string>& args) {
	double A, B, C, D;
	if (args.count("input") <= 0 && args.count("origin") <= 0 && args.count("direction") <= 0 && args.count("output1") <= 0 && args.count("output2") <= 0) {
		return 3;
	}
	std::regex regular("(\\()" "([0-9]*[.]?[0-9]+)" "(,)" "([0-9]*[.]?[0-9]+)" "(,)""([0-9]*[.]?[0-9]+)" "(\\))");
	std::cmatch result;
	if (std::regex_match(args.at("origin").c_str(), result, regular)) {
		origin.x = std::stof(result[2]);
		origin.y = std::stof(result[4]);
		origin.z = std::stof(result[6]);
	}
	else
	{
		return 3;
	}
	if (std::regex_match(args.at("direction").c_str(), result, regular)) {
		direction.x = std::stof(result[2]);
		direction.y = std::stof(result[4]);
		direction.z = std::stof(result[6]);
		if (direction.Length() <= 0) {
			return 1;
		}
	}
	else
	{
		return 3;
	}
	input.open(args.at("input"));
	output1.open(args.at("output1"));
	output2.open(args.at("output2"));
	if (!input.is_open() || !output1.is_open() || !output2.is_open()) {
		return 2;
	}
	return 0;

}