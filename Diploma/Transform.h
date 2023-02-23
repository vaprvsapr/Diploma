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

cv::Mat TransformImage(
	const Camera& camera,
	size_t new_height
)
{
	auto abs_size = FindNewImageSize(camera);
	double
		vertical_min = abs_size[0],
		vertical_delta= abs_size[1] - abs_size[0],
		horizontal_min = abs_size[2],
		horizontal_delta = abs_size[3] - abs_size[2];

	ImageSize new_image_size = {
		new_height,
		size_t(new_height / vertical_delta * horizontal_delta)
	};

	cv::Mat new_image = cv::Mat::zeros(new_image_size.height,
		new_image_size.width, CV_8UC3);

	for (size_t i = 0; i < camera.image_size.height; i++)
	{
		for (size_t j = 0; j < camera.image_size.width; j++)
		{
			Coordinate3D pixel3d =
				GetPixelCoordinate(camera, { i, j });
			Coordinate2D pixel = Projection(camera.position, pixel3d);

			pixel.x -= vertical_min;
			pixel.y -= horizontal_min;
			
			Pixel new_pixel = {
				size_t(int(new_image_size.height - 1) -
				pixel.x / vertical_delta * 
					(new_image_size.height - 1)),
				size_t(int(new_image_size.width - 1) -
				pixel.y / horizontal_delta *
					(new_image_size.width - 1))
			};

			new_image.at<cv::Vec3b>(
				new_pixel.vertical,
				new_pixel.horizontal
				) =
				camera.image.at<cv::Vec3b>(i, j);
		}
	}
	return new_image;
}
 
cv::Mat TransformImages(
	const vector<Camera> cameras,
	size_t new_height
)
{
	array<double, 4> abs_size = { 10e9, -10e9, 10e9, -10e9 };
	for (size_t i = 0; i < cameras.size(); i++)
	{
		auto local = FindNewImageSize(cameras[i]);
		if (local[0] < abs_size[0])
			abs_size[0] = local[0];
		if (local[1] > abs_size[1])
			abs_size[1] = local[1];
		if (local[2] < abs_size[2])
			abs_size[2] = local[2];
		if (local[3] > abs_size[3])
			abs_size[3] = local[3];
	}

	double
		vertical_min = abs_size[0],
		vertical_delta = abs_size[1] - abs_size[0],
		horizontal_min = abs_size[2],
		horizontal_delta = abs_size[3] - abs_size[2];

	ImageSize new_image_size = {
		new_height,
		size_t(new_height / vertical_delta * horizontal_delta)
	};

	cv::Mat new_image = cv::Mat::zeros(new_image_size.height,
		new_image_size.width, CV_8UC3);

	for (size_t camera_index = 0; camera_index < cameras.size(); camera_index++)
	{
		for (size_t i = 0; i < cameras[camera_index].image_size.height; i++)
		{
			for (size_t j = 0; j < cameras[camera_index].image_size.width; j++)
			{
				Coordinate3D pixel3d =
					GetPixelCoordinate(cameras[camera_index], {i, j});
				Coordinate2D pixel_coordinate = Projection(cameras[camera_index].position, pixel3d);

				pixel_coordinate.x -= vertical_min;
				pixel_coordinate.y -= horizontal_min;

				Pixel new_pixel = {
					size_t(int(new_image_size.height - 1) -
					pixel_coordinate.x / vertical_delta *
						(new_image_size.height - 1)),
					size_t(int(new_image_size.width - 1) -
					pixel_coordinate.y / horizontal_delta *
						(new_image_size.width - 1))
				};

				new_image.at<cv::Vec3b>(
					new_pixel.vertical,
					new_pixel.horizontal
					) =
					cameras[camera_index].image.at<cv::Vec3b>(i, j);
			}
		}
	}

	return new_image;
}