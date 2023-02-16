#pragma once

#include <cmath>
#include "Structures.h"

enum Axis
{
	X, Y, Z
};

void Rotate(
	Axis axis,
	Coordinate3D& coordinate, 
	const double& angle)
{
	switch (axis)
	{
	case X:
		coordinate =
		{
			coordinate.x,
			cos(angle) * coordinate.y -
			sin(angle) * coordinate.z,
			sin(angle) * coordinate.y +
			cos(angle) * coordinate.z
		};
		break;
	case Y:
		coordinate =
		{
			cos(angle) * coordinate.x +
			sin(angle) * coordinate.z,
			coordinate.y,
		   -sin(angle) * coordinate.x +
			cos(angle) * coordinate.z
		};
		break;
	case Z:
		coordinate = 
		{
			cos(angle) * coordinate.x -
			sin(angle) * coordinate.y,
			sin(angle) * coordinate.x + 
			cos(angle) * coordinate.y,
			coordinate.z
		};
		break;
	}
}

void RotateZ(
	Coordinate2D& coordinate, 
	const double& angle)
{
	coordinate =
	{
		cos(-angle) * coordinate.x -
		sin(-angle) * coordinate.y,
		sin(-angle) * coordinate.x +
		cos(-angle) * coordinate.y
	};
}