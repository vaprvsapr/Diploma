#pragma once
#include "Structures.h"
#include <iostream>


bool IsPointInsideATriangle(
	Coordinate2D pixel,
	array<Coordinate2D, 3>triangle)
{
	double a = (triangle[0].x - pixel.x) * (triangle[1].y - triangle[0].y)
		- (triangle[1].x - triangle[0].x) * (triangle[0].y - pixel.y);
	double b = (triangle[1].x - pixel.x) * (triangle[2].y - triangle[1].y)
		- (triangle[2].x - triangle[1].x) * (triangle[1].y - pixel.y);
	double c = (triangle[2].x - pixel.x) * (triangle[0].y - triangle[2].y)
		- (triangle[0].x - triangle[2].x) * (triangle[2].y - pixel.y);

	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}