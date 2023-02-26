#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iomanip>

#include "Structures.h"
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
	ss << setprecision(5)
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