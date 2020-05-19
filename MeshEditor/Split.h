#pragma once
#include <fstream>
#include "Command.h"
#include <regex>
#include "Vector3.h"
#include "Point.h"
class Split : public Command
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	int Parse(const std::map<std::string, std::string>& args);
	const std::string& name = "Split";
	std::ifstream input;
	std::ofstream output1;
	std::ofstream output2;
	std::ofstream file;
	Point origin;
	Vector3 direction;
};