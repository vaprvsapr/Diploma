#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <array>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Coordinate3D
{
	double x;
	double y;
	double z;
};

Coordinate3D operator+(
	const Coordinate3D& lhs, 
	const Coordinate3D& rhs
)
{
	return
	{
		lhs.x + rhs.x,
		lhs.y + rhs.y,
		lhs.z + rhs.z
	};
}

bool operator==(const Coordinate3D& lhs, const Coordinate3D& rhs)
{
	return make_tuple(lhs.x, lhs.y, lhs.z) == make_tuple(rhs.x, rhs.y, rhs.z);
}

struct Coordinate2D
{
	double x;
	double y;
};

struct EulerAngles
{
	double roll;
	double pitch;
	double yaw;
};

struct ImageSize
{
	size_t height;
	size_t width;
};

struct Size2D
{
	double height;
	double width;
};

struct FieldOfView
{
	double vertical;
	double horizontal;
};

struct Pixel
{
	size_t vertical;
	size_t horizontal;
};

struct Camera
{
	cv::Mat image;
	Size2D matrix_size;
	ImageSize image_size;

	double horizontal_field_of_view;
	double focal_length;

	Coordinate3D position;
	EulerAngles orientation;

	Camera(
		cv::Mat _image,
		Coordinate3D _position,
		EulerAngles _orientation,
		double _horizontal_field_of_view
	)
		: image(_image)
		, position(_position)
		, orientation(_orientation)
		, horizontal_field_of_view(_horizontal_field_of_view)
	{
		image_size = {
			size_t(_image.size().height),
			size_t(_image.size().width)
		};
		matrix_size = {
			double(image_size.height) / 1000,
			double(image_size.width) / 1000
		};
		focal_length = 
			matrix_size.width / 2 / 
			tan(horizontal_field_of_view / 2);
	}

	Camera(
		Coordinate3D _position,
		EulerAngles _orientation,
		double _horizontal_field_of_view,
		ImageSize _image_size
	)
		: position(_position)
		, orientation(_orientation)
		, horizontal_field_of_view(_horizontal_field_of_view)
		, image_size(_image_size)
	{
		matrix_size = {
			double(image_size.height) / 1000,
			double(image_size.width) / 1000
		};
		focal_length =
			matrix_size.width / 2 /
			tan(horizontal_field_of_view / 2);
		image = cv::Mat::zeros(
			image_size.height,
			image_size.width,
			CV_8UC3
		);
	}
};

struct ReferenceImage
{
	cv::Mat reference_image;
	double spatial_resolution;
	Size2D physical_size;
	ImageSize image_size;

	ReferenceImage(cv::Mat ref_img, const double& spatial_res)
	{
		reference_image = ref_img;
		spatial_resolution = spatial_res;
		image_size = { size_t(ref_img.size().height), 
			size_t(ref_img.size().width)};
		physical_size = {
			image_size.height * spatial_resolution,
			image_size.width * spatial_resolution
		};
	}

	ReferenceImage(cv::Mat ref_img, Size2D phys_size)
	{
		reference_image = ref_img;
		image_size = { size_t(ref_img.size().height),
			size_t(ref_img.size().width) };
		spatial_resolution = phys_size.height / image_size.height;
		physical_size = phys_size;
	}
};
