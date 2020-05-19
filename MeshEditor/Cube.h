#pragma once
#include "Command.h"
#include "Figure.h"
#include <regex>
#include "Vector3.h"
#include "Point.h"
#include <cmath>
#include <iostream>
class Cube : public Command, Figure
{
public:
	const std::string& getName() const override;
	int execute(const std::map<std::string, std::string>& args) override;
private:
	const std::string& name = "Cube";
	float L;
	Point origin;
	Vec koords[8];


	int Parse(const std::map<std::string, std::string>& args) ;
	void CalculateKoords(TriangleSoup & ts);

	double distance(double A, double B, double C, double D, Vec point) {
		return (A*point.x + B * point.y + C * point.z + D) / sqrt(pow(A, 2) + pow(B, 2) + pow(C, 2));
	}

	void SliceTriangle(TriangleSoup & ts, Vec a, Vec b, Vec c)
	{
		double d1 = distance(1, 1, 1, 0, a);
		double d2 = distance(1, 1, 1, 0, b);
		double d3 = distance(1, 1, 1, 0, c);
		std::cout << d1 << " " << d2 << " " << d3 << "\n";
		if (d1 * d2 < 0.0f)
			Slice(ts, a, b, c, d1, d2, d3);

		// a to c crosses the clipping plane
		else if (d1 * d3 < 0.0f)
			Slice(ts, c, a, b, d3, d1, d2);

		// b to c crosses the clipping plane
		else if (d2 * d3 < 0.0f)
			Slice(ts, b, c, a, d2, d3, d1);

		// No clipping plane intersection; keep the whole triangle
		else {
			if (d1 < 0) {
				CreatePoligon(ts, a, b, c);
			}
		}

	}

	

	void Slice(TriangleSoup & ts, Vec a, Vec b, Vec c, double d1, double d2, double d3) {
		std::cout << d1 << " " << d2 << " " << d3;
		Vec ab(a.x + (d1 / (d1 - d2))*(b.x - a.x), a.y + (d1 / (d1 - d2))*(b.y - a.y), a.z + (d1 / (d1 - d2))*(b.z - a.z));
		if (d1 < 0.0f)
		{
			if (d3 < 0.0f)
			{
				Vec bc(b.x + (d2 / (d2 - d3))*(c.x - b.x), b.y + (d2 / (d2 - d3))*(c.y - b.y), b.z + (d2 / (d2 - d3))*(c.z - b.z));
				std::cout << 1 << std::endl;
				//CreatePoligon(ts, b, bc, ab);
				CreatePoligon(ts, bc, c, a);
				CreatePoligon(ts, ab, bc, a);
			}
			else
			{
				Vec ac(a.x + (d1 / (d1 - d3))*(c.x - a.x), a.y + (d1 / (d1 - d3))*(c.y - a.y), a.z + (d1 / (d1 - d3))*(c.z - a.z));
				CreatePoligon(ts, a, ab, ac);
				//CreatePoligon(ts, ab, b, c);
				//CreatePoligon(ts, ac, ab, c);
				std::cout << 2 << std::endl;
			}
		}
		else
		{
			// c to a crosses the clipping plane
			if (d3 < 0.0f)
			{
				// Calculate intersection point from a to c
				//Vec2 ac = a + (d1 / (d1 - d3)) * (c - a);
				Vec ac(a.x + (d1 / (d1 - d3))*(c.x - a.x), a.y + (d1 / (d1 - d3))*(c.y - a.y), a.z + (d1 / (d1 - d3))*(c.z - a.z));
				/*tri.Set(a, ab, ac);
				out.push_back(tri);

				tri.Set(ac, ab, b);
				out.push_back(tri);

				tri.Set(b, c, ac);
				out.push_back(tri);*/

				//CreatePoligon(ts, a, ab, ac);
				CreatePoligon(ts, ac, ab, b);
				CreatePoligon(ts, b, c, ac);

				std::cout << 3 << std::endl;
			}

			// b to c crosses the clipping plane
			else
			{
				// Calculate intersection point from b to c
				//Vec2 bc = b + (d2 / (d2 - d3)) * (c - b);
				Vec bc(b.x + (d2 / (d2 - d3))*(c.x - b.x), b.y + (d2 / (d2 - d3))*(c.y - b.y), b.z + (d2 / (d2 - d3))*(c.z - b.z));
				/*tri.Set(b, bc, ab);
				out.push_back(tri);

				tri.Set(a, ab, bc);
				out.push_back(tri);

				tri.Set(c, a, bc);
				out.push_back(tri);*/
				std::cout << 4 << std::endl;
				CreatePoligon(ts, b, bc, ab);
				//CreatePoligon(ts, a, ab, bc);
				//CreatePoligon(ts, c, a, bc);
			}
		}
		//CreatePoligon(ts, a, b, c);
		std::cout << 5 << std::endl;
	}
};