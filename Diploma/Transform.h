#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>

#include "Structures.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"

cv::Mat GetTransformedImage(
	Camera camera,
	size_t new_image_size)
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
		top_left = Projection(camera, top_left_3d),
		top_right = Projection(camera, top_right_3d),
		bottom_left = Projection(camera, bottom_left_3d),
		bottom_right = Projection(camera, bottom_right_3d);

	RotateZ(top_left, camera.orientation.yaw);
	RotateZ(top_right, camera.orientation.yaw);
	RotateZ(bottom_left, camera.orientation.yaw);
	RotateZ(bottom_right, camera.orientation.yaw);


}
