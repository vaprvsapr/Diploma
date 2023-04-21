#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <filesystem>
#include <exception>
#include <fstream>

#include "Structures.h"
#include "Transform.h"
#include "ReadCamera.h"

#include "CalculateOverlap.h"

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

vector<Camera> ReadCamerasFromDirectory(const string& directory)
{
	ifstream input;
	input.open(directory + "/trajectory.txt");
	vector<pair<Coordinate3D, EulerAngles>> trajectory;
	string line;
	while (getline(input, line))
	{
		stringstream ss(line);
		int camera_number;
		ss >> camera_number;

		string CAM;
		ss >> CAM;
		double pos_accuracy;
		trajectory.push_back({});
		ss >> trajectory[camera_number].first.x
			>> trajectory[camera_number].first.y
			>> trajectory[camera_number].first.z
			>> pos_accuracy
			>> trajectory[camera_number].second.yaw
			>> trajectory[camera_number].second.pitch
			>> trajectory[camera_number].second.roll
			>> pos_accuracy;

		trajectory[camera_number].first.z -= 130;
		trajectory[camera_number].second.roll /= 180 / 3.141592;
		trajectory[camera_number].second.pitch /= 180 / 3.141592;
		trajectory[camera_number].second.pitch = 3.141592 / 2 - trajectory[camera_number].second.pitch;
		trajectory[camera_number].second.yaw /= 180 / 3.141592;
		trajectory[camera_number].second.yaw += 3.141592 / 2;
	}

	filesystem::path cameras_path(directory);
	vector<Camera> cameras;
	cameras.resize(trajectory.size());

	for (auto& camera_path : filesystem::directory_iterator{ cameras_path })
	{
		stringstream ss;
		ss << camera_path.path();
		string str = ss.str();
		auto id = str.find("\\");
		string camera_name = { next(str.begin(), id + 2), prev(str.end()) };
		id = camera_name.find("CAM");
		if (id < 10) 
		{
			stringstream ss2(camera_name);
			int camera_number;
			ss2 >> camera_number;
			camera_name = directory + "/" + camera_name;

			Camera cam
			{
				cv::imread(camera_name, cv::IMREAD_COLOR),
				{trajectory[camera_number].first.x,
				trajectory[camera_number].first.y,
				trajectory[camera_number].first.z},
				{trajectory[camera_number].second.roll,
				trajectory[camera_number].second.pitch,
				trajectory[camera_number].second.yaw},
				1.0821//1.59
			};

			cameras[camera_number] = cam;
		}
	}
	return cameras;
}

void ConcatenateImagesInDirectoryReadTrajectoryFromFile(
	const string& directory,
	const double& spatial_resolution
)
{
	auto cameras = ReadCamerasFromDirectory(directory);

	cv::Mat result = TransformImagesDev(cameras, spatial_resolution);
	cv::imwrite(directory + "/res.tif", result);
}