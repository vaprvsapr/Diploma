#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Structures.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"

cv::Mat GetTransformedImage(
	const Camera& camera,
	size_t new_image_size)
{
	//Coordinate2D
	//	top_left = Projection(camera, GetPixelCoordinate(
	//		camera, { 0, 0 }));
		//top_right = Projection(camera, GetPixelCoordinate(
		//	camera, { 0, camera.image_size.width })),
		//bottom_left = GetPixelCoordinate(
		//	camera, { camera.image_size.height, 0 }),
		//bottom_right = GetPixelCoordinate(
		//	camera, { camera.image_size.height, 
		//	camera.image_size.width });