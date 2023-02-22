#pragma once

#include "Profile.h"
#include "Rotate.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"
#include "Transform.h"

using namespace std;


void Concatenate10Images()
{
	LOG_DURATION("Total");

	vector<string> image_paths =
	{
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-1000y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-900y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-800y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-700y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-600y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-500y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-400y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-300y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-200y0z1000r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/sequential_big/x-100y0z1000r0p60y0.png",
	};

	vector<Camera> cameras;
	for (size_t i = 0; i < 10; i++)
	{
		string image_path = "C:/Users/Mi/Pictures/Blender/sequential_big/x-" +
			to_string((10 - i) * 100) + "y0z1000r0p60y0.png";
		
		cameras.push_back({
			cv::imread(image_path, cv::IMREAD_COLOR),
			Coordinate3D{-(10 - double(i)) * 100, 0, 1000},
			EulerAngles{0, 3.141592 / 3, 0},
			0.69
			}
		);
	}

	cv::Mat new_img;
	{
		LOG_DURATION("GetTransformedImage");
		new_img = TransformImages(cameras, 1000);
	}

	{
		LOG_DURATION("cv::imwrite");
		cv::imwrite("C:/Users/Mi/Pictures/Blender/res/res.png", new_img);
	}
}

void ConcatenateRotatedImages()
{
	vector<string> image_paths =
	{
		"C:/Users/Mi/Pictures/Blender/rotation/xy0z500r0p60y0.png",
		"C:/Users/Mi/Pictures/Blender/rotation/xy0z500r0p60y45.png",
		"C:/Users/Mi/Pictures/Blender/rotation/xy0z500r0p60y90.png"
	};

	vector<Camera> cameras;
	for (size_t i = 0; i < image_paths.size(); i++)
	{
		string image_path = "C:/Users/Mi/Pictures/Blender/rotation/x0y0z500r0p60y" + to_string(i * 45) + ".png";

		cameras.push_back({
			cv::imread(image_path, cv::IMREAD_COLOR),
			Coordinate3D{0, 0, 1000},
			EulerAngles{0, 3.141592 / 3, 3.141592 / 4 * i},
			0.69
			}
		);
	}
	cv::Mat new_img;
	{
		LOG_DURATION("GetTransformedImage");
		new_img = TransformImages(cameras, 1000);
	}

	{
		LOG_DURATION("cv::imwrite");
		cv::imwrite("C:/Users/Mi/Pictures/Blender/res/res_rotation.png", new_img);
	}
}

void ConcatenateImagesWithChangingPitch()
{
	string path = "C:/Users/Mi/Pictures/Blender/changing_pitch/";
	vector<string> image_paths =
	{
		path + "x-1000y0z500r0p90y0.png",
		path + "x-1000y0z500r0p75y0.png",
		path + "x-1000y0z500r0p60y0.png",
		path + "x-1000y0z500r0p45y0.png",
		path + "x-1000y0z500r0p30y0.png"
	};

	vector<Camera> cameras;
	for (size_t i = 0; i < image_paths.size(); i++)
	{
		cameras.push_back({
			cv::imread(image_paths[i], cv::IMREAD_COLOR),
			Coordinate3D{-1000, 0, 500},
			EulerAngles{0, 3.141592 / 2 - i * 3.141592 / 12, 0},
			0.69
			}
		);
	}
	cv::Mat new_img;
	{
		LOG_DURATION("GetTransformedImage");
		new_img = TransformImages(cameras, 1000);
	}

	{
		LOG_DURATION("cv::imwrite");
		cv::imwrite(path + "res.png", new_img);
	}
}

void ConcatenateImagesWithChangingFieldOfView()
{
	string path = "C:/Users/Mi/Pictures/Blender/changing_field_of_view/";
	vector<string> image_paths =
	{
		path + "x-1000y0z500r0p60y0fov39.6.png",
		path + "x-1000y0z500r0p50y0fov30.png",
		path + "x-1000y0z500r0p40y0fov20.png",
		path + "x-1000y0z500r0p60y90fov90.png"
	};

	vector<Camera> cameras =
	{
		{cv::imread(image_paths[0], cv::IMREAD_COLOR), {-1000, 0, 500}, {0, 3.141592 / 3, 0}, 0.69 },
		{cv::imread(image_paths[1], cv::IMREAD_COLOR), {-1000, 0, 500}, {0, 3.141592 / 18 * 5, 0}, 3.141592 / 6 },
		{cv::imread(image_paths[2], cv::IMREAD_COLOR), {-1000, 0, 500}, {0, 3.141592 / 18 * 4, 0}, 3.141592 / 9 },
		{cv::imread(image_paths[3], cv::IMREAD_COLOR), {-1000, 0, 500}, {0, 3.141592 / 3, 3.141592 / 2}, 3.141592 / 2 }
	};

	cv::Mat new_img;
	{
		LOG_DURATION("GetTransformedImage");
		new_img = TransformImages(cameras, 1000);
	}

	{
		LOG_DURATION("cv::imwrite");
		cv::imwrite(path + "res.png", new_img);
	}
}

void ConcatenateImagesWithChangingRoll()
{
	string path = "C:/Users/Mi/Pictures/Blender/changing_roll/";
	vector<string> image_paths =
	{
		path + "x1000y0z500r0p60y180.png",
		path + "x1000y0z500r15p60y180.png",
	};

	vector<Camera> cameras =
	{
		{cv::imread(image_paths[0], cv::IMREAD_COLOR), {1000, 0, 500}, {0, 3.141592 / 3, 0}, 0.69 },
		{cv::imread(image_paths[1], cv::IMREAD_COLOR), {1000, 0, 500}, {-3.141592 / 180 * 25, 3.141592 / 3, 0}, 0.69},
	};

	cv::Mat new_img;
	{
		LOG_DURATION("GetTransformedImage");
		new_img = TransformImages(cameras, 1000);
	}

	{
		LOG_DURATION("cv::imwrite");
		cv::imwrite(path + "res.png", new_img);
	}
}