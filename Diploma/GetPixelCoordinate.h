#pragma once

#include "Structures.h"
#include "Rotate.h"

Coordinate3D GetPixelCoordinate(
	Camera camera,
	const Pixel& pixel)
{
	Coordinate3D pixel_coordinate =
	{
		camera.focal_length,
		camera.matrix_size.width *
		(camera.image_size.width / 2 - pixel.horizontal) /
		camera.image_size.width,
		camera.matrix_size.height *
		(camera.image_size.height / 2 - pixel.vertical) /
		camera.image_size.height
	};

	Rotate(Z, pixel_coordinate, camera.orientation.yaw);
	Rotate(Y, pixel_coordinate, camera.orientation.pitch);
	Rotate(X, pixel_coordinate, camera.orientation.roll);

	pixel_coordinate.x += camera.position.x;
	pixel_coordinate.y += camera.position.y;
	pixel_coordinate.z += camera.position.z;

	return pixel_coordinate;
}
