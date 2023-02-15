#pragma once

#include "Structures.h"

Coordinate2D Projection(
	const Camera& camera,
	Coordinate3D& pixel_coordinate)
{
	Coordinate3D pixel_coordinate_on_plane = { 0, 0, 0 };

	if (pixel_coordinate.x - camera.position.x == 0)
		pixel_coordinate_on_plane.x = camera.position.x;
	else
		pixel_coordinate_on_plane.x =
		(pixel_coordinate_on_plane.z - camera.position.z) /
		(pixel_coordinate.z - camera.position.z) *
		(pixel_coordinate.x - camera.position.x) + 
		camera.position.x;

	if (pixel_coordinate.y - camera.position.y == 0)
		pixel_coordinate_on_plane.y = camera.position.y;
	else
		pixel_coordinate_on_plane.y =
		(pixel_coordinate_on_plane.z - camera.position.z) /
		(pixel_coordinate.z - camera.position.z) *
		(pixel_coordinate.y - camera.position.y) + 
		camera.position.y;

	return { 
		pixel_coordinate_on_plane.x, 
		pixel_coordinate_on_plane.y
	};
}