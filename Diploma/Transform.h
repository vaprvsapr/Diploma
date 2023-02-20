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
	size_t new_x_image_size)
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

	//cout << "tl: " << top_left.x << " " << top_left.y
	//	<< "\ntr: " << top_right.x << " " << top_right.y
	//	<< "\nbl: " << bottom_left.x << " " << bottom_left.y
	//	<< "\nbr: " << bottom_right.x << " " << bottom_right.y << endl;

	double
		x_min = min({ top_left.x, top_right.x,
			bottom_left.x, bottom_right.x }),
		x_max = max({ top_left.x, top_right.x,
			bottom_left.x, bottom_right.x }) - x_min,
		y_min = min({ top_left.y, top_right.y,
			bottom_left.y, bottom_right.y }),
		y_max = max({ top_left.y, top_right.y,
			bottom_left.y, bottom_right.y }) - y_min;

	cout << "x_min:" << x_min
		<< ", x_max:" << x_max
		<< ", y_min:" << y_min
		<< ", y_max:" << y_max << endl;

	ImageSize new_image_size = {
		new_x_image_size,
		size_t(new_x_image_size / x_max * y_max)
	};

	cout << "new_height: " << new_x_image_size << " , new_width: "
		<< new_image_size.width << endl;

	cv::Mat new_image = cv::Mat::zeros(new_image_size.height,
		new_image_size.width, CV_8UC3);

	for (size_t i = 0; i < camera.image_size.height; i++)
	{
		for (size_t j = 0; j < camera.image_size.width; j++)
		{
			Coordinate3D pixel3d =
				GetPixelCoordinate(camera, { i, j });
			Coordinate2D pixel = Projection(camera, pixel3d);

			pixel.x -= x_min;
			pixel.y -= y_min;
			
			Pixel new_pixel = {
				size_t(int(new_image_size.height) -
				pixel.x / x_max * (new_image_size.height - 1)),
				size_t(int(new_image_size.width) -
				pixel.y / y_max * (new_image_size.width - 1))
			};

			//cout << "pixel_x:" << pixel.x 
			//	<< ", pixel_y:" << pixel.y 
			//	<< ", i:" << i << ", j:" << j 
			//	<< ", npv:" << new_pixel.vertical 
			//	<< ", nph:" << new_pixel.horizontal << "\n";

			new_image.at<cv::Vec3b>(
				new_pixel.vertical,
				new_pixel.horizontal
				) =
				camera.image.at<cv::Vec3b>(i, j);
		

		}
	}
			return new_image;
	return {};
}
 