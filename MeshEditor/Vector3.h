#pragma once
#include <cmath>
struct Vector3
{
	double x;
	double y;
	double z;

	double Length() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	void SetKoords(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};