#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <algorithm>

#include "Structures.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"

array<double, 4> FindNewImageSize(const Camera& camera)
{
	Coordinate3D
		top_left_3d = GetPixelCoordinate(camera,
			{ 0, 0 }),
		top_right_3d = GetPixelCoordinate(camera,
			{ 0, camera.image_size.width }),
		bottom_left_3d = GetPixelCoordinate(camera,
			{ camera.image_size.height, 0 }),
		bottom_right_3d = GetPixelCoordinate(camera,
			{ camera.image_size.height,
			camera.image_size.width });

	Coordinate2D
		top_left = Projection(camera.position, top_left_3d),
		top_right = Projection(camera.position, top_right_3d),
		bottom_left = Projection(camera.position, bottom_left_3d),
		bottom_right = Projection(camera.position, bottom_right_3d);

	double
		vertical_min = min({ top_left.x, top_right.x,
			bottom_left.x, bottom_right.x }),
		vertical_max = max({ top_left.x, top_right.x,
			bottom_left.x, bottom_right.x }),
		horizontal_min = min({ top_left.y, top_right.y,
			bottom_left.y, bottom_right.y }),
		horizontal_max = max({ top_left.y, top_right.y,
			bottom_left.y, bottom_right.y });

	return {
		vertical_min, vertical_max,
		horizontal_min, horizontal_max
	};
}