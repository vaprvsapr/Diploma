#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <filesystem>
#include <exception>

#include "Structures.h"
#include "Transform.h"
#include "ReadCamera.h"


void ConcatenateImagesInDirectory(
	const string& directory,
	const double& spatial_resolution
)
{
	filesystem::path cameras_path(directory);
	vector<Camera> cameras;

	for (auto& camera_path : filesystem::directory_iterator{ cameras_path })
	{
		stringstream ss;
		ss << camera_path.path();
		string str = ss.str();
		auto id = str.find("\\");
		string camera_name = { next(str.begin(), id + 2), prev(str.end()) };
		camera_name = directory + "/" + camera_name;

		Camera cam = ReadCamera(camera_name);
		cameras.push_back(cam);
	}

	cv::Mat result = TransformImages(cameras, spatial_resolution);
	cv::imwrite(directory + "/res.tif", result);
}

void ConcatenateImagesInDirectoryDev(
	const string& directory,
	const double& spatial_resolution
)
{
	filesystem::path cameras_path(directory);
	vector<Camera> cameras;

	for (auto& camera_path : filesystem::directory_iterator{ cameras_path })
	{
		stringstream ss;
		ss << camera_path.path();
		string str = ss.str();
		auto id = str.find("\\");
		string camera_name = { next(str.begin(), id + 2), prev(str.end()) };
		camera_name = directory + "/" + camera_name;

		Camera cam = ReadCamera(camera_name);
		cameras.push_back(cam);
	}

	cv::Mat result = TransformImagesDev(cameras, spatial_resolution);
	cv::imwrite(directory + "/res.tif", result);
}