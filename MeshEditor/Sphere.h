#pragma once
#define _USE_MATH_DEFINES 
#include "Command.h"
#include "Figure.h"
#include <fstream>
#include <regex>
#include "Point.h"
#include "STLParser.h"
#include <vector>

#include <cmath>
class Sphere : public Command, Figure
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	void CalculateKoords(TriangleSoup & ts);
	const std::string& name = "Sphere";
	float R;
	Point origin;
	std::vector<Vec> koords;
	int Parse(const std::map<std::string, std::string>& args);
};
