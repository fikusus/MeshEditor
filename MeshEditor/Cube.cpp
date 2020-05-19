#include "Cube.h"
#include <iostream>
const std::string& Cube::getName() const {

	return name;
}

int Cube::execute(const std::map<std::string, std::string>& args) {
	int parseResult = Parse(args);
	if (parseResult != 0) {
		return parseResult;
	}
	TriangleSoup triangleSoup;
	CalculateKoords(triangleSoup);
	STLParser parser;
	try {
		parser.write(triangleSoup, args.at("filepath"));
	}
	catch (std::ios_base::failure) {
		return 2;
	}

	
	return 0;
}

int Cube::Parse(const std::map<std::string, std::string>& args) {
	if (args.count("L") <= 0 && args.count("filepath") <= 0 && args.count("origin") <= 0) {
		return 3;
	}
	std::regex regular("([0-9]*[.]?[0-9]+)");
	std::cmatch result;
	if (std::regex_match(args.at("L").c_str(), regular)) {
		L = std::stof(args.at("L"));
		if (L <= 0) {
			return 1;
		}
	}
	else {
		return 3;
	}
	regular = ("(\\()" "([0-9]*[.]?[0-9]+)" "(,)" "([0-9]*[.]?[0-9]+)" "(,)""([0-9]*[.]?[0-9]+)" "(\\))");
	if (std::regex_match(args.at("origin").c_str(), result, regular)) {
		origin.x = std::stof(result[2]);
		origin.y = std::stof(result[4]);
		origin.z = std::stof(result[6]);
	}
	else
	{
		return 3;
	}
	return 0;
}


void Cube::CalculateKoords(TriangleSoup & ts) {
	double lTemp = L / 2;
	koords[0].SetKoords(origin.x - lTemp, origin.y + lTemp, origin.z - lTemp);
	koords[1].SetKoords(origin.x + lTemp, origin.y + lTemp, origin.z - lTemp);
	koords[2].SetKoords(origin.x + lTemp, origin.y - lTemp, origin.z - lTemp);
	koords[3].SetKoords(origin.x - lTemp, origin.y - lTemp, origin.z - lTemp);
	koords[4].SetKoords(origin.x - lTemp, origin.y + lTemp, origin.z + lTemp);
	koords[5].SetKoords(origin.x + lTemp, origin.y + lTemp, origin.z + lTemp);
	koords[6].SetKoords(origin.x + lTemp, origin.y - lTemp, origin.z + lTemp);
	koords[7].SetKoords(origin.x - lTemp, origin.y - lTemp, origin.z + lTemp);


	SliceTriangle(ts, koords[0], koords[1], koords[3]);
	SliceTriangle(ts, koords[1], koords[2], koords[3]);

	SliceTriangle(ts, koords[0], koords[3], koords[4]);
	SliceTriangle(ts, koords[4], koords[3], koords[7]);

	SliceTriangle(ts, koords[4], koords[7], koords[6]);
	SliceTriangle(ts, koords[4], koords[6], koords[5]);

	SliceTriangle(ts, koords[1], koords[5], koords[2]);
	SliceTriangle(ts, koords[5], koords[6], koords[2]);

	SliceTriangle(ts, koords[1], koords[0], koords[4]);
	SliceTriangle(ts, koords[4], koords[5], koords[1]);

	SliceTriangle(ts, koords[6], koords[7], koords[3]);
	SliceTriangle(ts, koords[6], koords[3], koords[2]);

	/*CreatePoligon(ts, koords[0], koords[1], koords[3]);
	CreatePoligon(ts, koords[1], koords[2], koords[3]);

	CreatePoligon(ts, koords[0], koords[3], koords[4]);
	CreatePoligon(ts, koords[4], koords[3], koords[7]);

	CreatePoligon(ts, koords[4], koords[7], koords[6]);
	CreatePoligon(ts, koords[4], koords[6], koords[5]);

	CreatePoligon(ts, koords[1], koords[5], koords[2]);
	CreatePoligon(ts, koords[5], koords[6], koords[2]);

	CreatePoligon(ts, koords[1], koords[0], koords[4]);
	CreatePoligon(ts, koords[4], koords[5], koords[1]);

	CreatePoligon(ts, koords[6], koords[7], koords[3]);
	CreatePoligon(ts, koords[6], koords[3], koords[2]);
	*/


	//CreatePoligon(ts, *new Vec(20, 0, 3), *new Vec(0, 0, 3), *new Vec(0, 20, 3));
}
