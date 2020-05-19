#include "Sphere.h"
const std::string& Sphere::getName() const {

	return name;
}

int Sphere::execute(const std::map<std::string, std::string>& args) {
	int parseResult = Parse(args);
	if (parseResult != 0) {
		return parseResult;
	}
	STLParser parser;
	TriangleSoup triangleSoup;
	CalculateKoords(triangleSoup);
	try {
		parser.write(triangleSoup, args.at("filename"));
	}
	catch (std::ios_base::failure) {
		return 2;
	}
	return 0;
}

int Sphere::Parse(const std::map<std::string, std::string>& args) {
	if (args.count("R") <= 0 && args.count("filename") <= 0 && args.count("origin") <= 0) {
		return 3;
	}
	std::regex regular("([0-9]*[.]?[0-9]+)");
	std::cmatch result;
	if (std::regex_match(args.at("R").c_str(), regular)) {
		R = std::stof(args.at("R"));
		if (R <= 0) {
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

void Sphere::CalculateKoords(TriangleSoup & ts) {
	int sectorCount = 36;
	int stackCount = 18;
	float sectorStep = 2 * M_PI / sectorCount;
	float stackStep = M_PI / stackCount;
	float sectorAngle, stackAngle;
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = M_PI / 2 - i * stackStep;
		float xy = R * cosf(stackAngle);
		float z = R * sinf(stackAngle);
		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep; 
			Vec vertex;
			vertex.x = xy * cosf(sectorAngle) + origin.x;
			vertex.y = xy * sinf(sectorAngle) + origin.y;
			vertex.z = z + origin.z;
			koords.push_back(vertex);
		}
	}

	Vec v1, v2, v3, v4;
	int i, j, vi1, vi2;
	for (int i = 0; i < stackCount; ++i)
	{
		vi1 = i * (sectorCount + 1);
		vi2 = (i + 1) * (sectorCount + 1);

		for (j = 0; j < sectorCount; ++j, ++vi1, ++vi2)
		{
			v1 = koords[vi1];
			v2 = koords[vi2];
			v3 = koords[vi1 + 1];
			v4 = koords[vi2 + 1];
			if (i == 0)
			{
				CreatePoligon(ts, *new Vec(v1.x, v1.y, v1.z), *new Vec(v2.x, v2.y, v2.z), *new Vec(v4.x, v4.y, v4.z));
			}
			else if (i == (stackCount - 1))
			{
				CreatePoligon(ts, *new Vec(v1.x, v1.y, v1.z), *new Vec(v2.x, v2.y, v2.z), *new Vec(v3.x, v3.y, v3.z));
			}
			else 
			{
				CreatePoligon(ts, *new Vec(v1.x, v1.y, v1.z), *new Vec(v2.x, v2.y, v2.z), *new Vec(v3.x, v3.y, v3.z));
				CreatePoligon(ts, *new Vec(v3.x, v3.y, v3.z), *new Vec(v2.x, v2.y, v2.z), *new Vec(v4.x, v4.y, v4.z));
			}
		}
	}
}

