#pragma once
#include "STLParser.h"
class Figure
{
	protected:
		Vec VectorNormal(Vec m1, Vec m2, Vec m3);

	void CreatePoligon(TriangleSoup & triangleSoup, Vec a, Vec b, Vec c);
};

