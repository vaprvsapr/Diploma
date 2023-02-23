#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Structures.h"
#include <iomanip>

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

Camera ReadCamera(const string& camera_path)
{
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

	Camera camera
	{
		cv::imread(camera_path, cv::IMREAD_COLOR),
		{x, y, z},
		{roll, pitch, yaw},
		horizontal_fiel_of_view
	};

	return camera;
}