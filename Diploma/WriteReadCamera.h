#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Structures.h"
#include <iomanip>
#include <exception>
#include "GetCamera.h"

void WriteCamera(Camera camera, const string& directory)
{
	stringstream ss;
	ss << setprecision(3)
		<< "x" << camera.position.x
		<< "y" << camera.position.y
		<< "z" << camera.position.z
		<< "r" << camera.orientation.roll
		<< "p" << camera.orientation.pitch
		<< "y" << camera.orientation.yaw
		<< "fov" << camera.horizontal_field_of_view
		<< ".tif";

	string path = directory + "/" + "CAMERA" + ss.str();
	
	cv::imwrite(path, camera.image);
}

void WriteCameraWithIndex(Camera camera, const string& directory, const size_t index)
{
	stringstream ss;
	ss << setprecision(3)
		<< "x" << camera.position.x
		<< "y" << camera.position.y
		<< "z" << camera.position.z
		<< "r" << camera.orientation.roll
		<< "p" << camera.orientation.pitch
		<< "y" << camera.orientation.yaw
		<< "fov" << camera.horizontal_field_of_view
		<< ".tif";

	string path = directory + "/" + to_string(index) + "CAMERA" + ss.str();

	cv::imwrite(path, camera.image);
}


Camera ReadCamera(const string& camera_path)
{
	cout << camera_path << endl;
	auto id = camera_path.find("CAMERA");
	stringstream ss(camera_path);
	ss.ignore(id + 6);
	double
		x, y, z,
		roll, pitch, yaw,
		horizontal_fiel_of_view;

	ss.ignore(1);
	ss >> x;
	ss.ignore(1);
	ss >> y;
	ss.ignore(1);
	ss >> z;
	ss.ignore(1);
	ss >> roll;
	ss.ignore(1);
	ss >> pitch;
	ss.ignore(1);
	ss >> yaw;
	ss.ignore(3);
	ss >> horizontal_fiel_of_view;

	cout << "camera path: " << endl << camera_path << endl;

	Camera camera
	{
		cv::imread(camera_path, cv::IMREAD_COLOR),
		{x, y, z},
		{roll, pitch, yaw},
		horizontal_fiel_of_view
	};

	cout << camera.image_size.height << endl;

	return camera;
}

void CreateSetOfImages(
	ReferenceImage reference_image,
	vector<Coordinate3D> positions,
	vector<EulerAngles> orientations,
	double horizontal_field_of_view,
	ImageSize image_size,
	const string& directory
)
{
	if (positions.size() != orientations.size())
	{
		throw logic_error(
			"positions.size() != orientations.size()");
	}



	for (size_t i = 0; i < positions.size(); i++)
	{
		auto camera = GetCamera(
			reference_image,
			Camera{
				positions[i],
				orientations[i],
				horizontal_field_of_view,
				image_size
			}
		);
		WriteCameraWithIndex(camera, directory, i);
	}
}

#include <filesystem>

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