#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Structures.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"

using namespace std;

Camera GetCamera(
	ReferenceImage reference_image,				// референсное изображение
	Camera ref_camera
)
{
	Camera camera(
		ref_camera.position,
		ref_camera.orientation,
		ref_camera.horizontal_field_of_view,
		ref_camera.image_size
	);
	for (size_t i = 0; i < camera.image_size.height; i++)
	{
		for (size_t j = 0; j < camera.image_size.width; j++)
		{
			Coordinate3D pixel_coordinate3d = 
				GetPixelCoordinate(camera, { i, j });
			Coordinate2D pixel_coordinate2d =
				Projection(camera.position, pixel_coordinate3d);

			size_t ref_i = size_t(
				pixel_coordinate2d.x /
				reference_image.spatial_resolution);
			size_t ref_j = size_t(
				pixel_coordinate2d.y / 
				reference_image.spatial_resolution);

			if ((ref_i < 0) or
				(ref_i >= reference_image.image_size.height) or
				(ref_j < 0) or
				(ref_j >= reference_image.image_size.width))
			{
				camera.image.at<cv::Vec3b>(i, j) = {};
			}
			else
			{
				camera.image.at<cv::Vec3b>(i, j) =
					reference_image.reference_image.at<cv::Vec3b>(
						ref_i,
						ref_j);
			}
		}
	}
	return camera;
}
