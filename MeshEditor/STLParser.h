#pragma once
#include <vector>
#include <string>
#include <fstream>

struct Vec {
	double x, y, z;
	void SetKoords(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vec() {
		x = y = z = 0;
	}
	Vec(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	double Length() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	friend std::ostream& operator<< (std::ostream &out, const Vec &vec);
};




struct Vertex
{
	Vec pos;
	Vec normal;
	Vertex(Vec pos, Vec normal) {
		this->pos = pos;
		this->normal = normal;
	}
};
using TriangleSoup = std::vector<Vertex>;
class STLParser
{
public:
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& triangleSoup, const std::string& filename);
private:
};
