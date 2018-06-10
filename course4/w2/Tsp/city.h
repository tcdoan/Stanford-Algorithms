#pragma once
#include <cmath>

struct City
{
	double x;
	double y;
	City(double x, double y) : x(x), y(y)
	{
	}

	double dist(City other)
	{
		return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
	}
};