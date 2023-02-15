#pragma 

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

struct MatrixSize
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
	MatrixSize matrix_size;
	ImageSize image_size;
	FieldOfView field_of_view;
	double focal_length;

	Coordinate3D position;
	EulerAngles orientation;

	Camera(
		cv::Mat _image,
		Coordinate3D _position,
		EulerAngles _orientation,
		MatrixSize _matrix_size,
		FieldOfView _field_of_view)
		: image(_image)
		, position(_position)
		, orientation(_orientation)
		, matrix_size(_matrix_size)
		, field_of_view(_field_of_view)
	{
		image_size = {
			size_t(_image.size().height),
			size_t(_image.size().width) 
		};
		focal_length = 
			_matrix_size.width / 2 / 
			tan(_field_of_view.horizontal);
	}
};