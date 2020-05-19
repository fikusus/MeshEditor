#include "Figure.h"

Vec Figure::VectorNormal(Vec m1, Vec m2, Vec m3) {
	Vec* p1 = new Vec(m2.x - m1.x, m2.y - m1.y, m2.z - m1.z);
	Vec* p2 = new Vec(m3.x - m1.x, m3.y - m1.y, m3.z - m1.z);
	return *new Vec(p1->y*p2->z - p1->z*p2->y, p1->z*p2->x - p1->x*p2->z, p1->x*p2->y - p1->y*p2->x);
}

void Figure::CreatePoligon(TriangleSoup & triangleSoup, Vec a, Vec b, Vec c) {
	Vec vectorNormalTemp = VectorNormal(a, b, c);
	triangleSoup.push_back(Vertex(a, vectorNormalTemp));
	triangleSoup.push_back(Vertex(b, vectorNormalTemp));
	triangleSoup.push_back(Vertex(c, vectorNormalTemp));
}