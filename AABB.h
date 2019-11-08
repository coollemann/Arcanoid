#pragma once


struct Point {
	float x, y;
	Point(): x(0.0f), y(0.0f) {}
};

struct AABB {
	
	Point center;
	float r[2];
	AABB(): r{ 0.0f, 0.0f } {}
};

