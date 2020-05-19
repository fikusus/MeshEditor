#include "STLParser.h"

std::ostream& operator<< (std::ostream &out, const Vec &vec)
{
	out << vec.x << " " << vec.y << " " << vec.z;

	return out;
}

void STLParser::write(const TriangleSoup& triangleSoup, const std::string& filename) {
	std::ofstream out(filename);
	if (!out.is_open()) {
		throw std::ios_base::failure("error to open file");
	}
	out << std::scientific  << "solid " << std::endl;
	for (int i = 0; i < triangleSoup.size(); i += 3) {
		out << "facet normal " << triangleSoup[i].normal << std::endl << "outer loop\n";
		for (int j = i; j < i + 3; j++) {
			out << "vertex " << triangleSoup[j].pos << std::endl;
		}
		out << "endloop\nendfacet\n";
	}
	out << "endsolid";
	
}