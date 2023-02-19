#pragma once
#include <iostream>
#include "Structures.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"


void Test()
{
	cv::Mat img = cv::imread("C:/Users/Mi/Desktop/img.jpg", 
		cv::IMREAD_COLOR);

	Camera cam(
		img, 
		Coordinate3D{ 0, 0, 100 },
		EulerAngles{ 0, 0, 0 }, 
		MatrixSize{ 1, 1 },
		FieldOfView{ 1.57 / 2, 1.57 / 2 }
	);
	{
		cout << "Test: GetPixelCoordinate" << endl;
		
		auto pixel_coordinate =
			GetPixelCoordinate(cam, { 0, 0 });
		cout << "pixel_coordinate: x="
			<< pixel_coordinate.x << ", y="
			<< pixel_coordinate.y << ", z="
			<< pixel_coordinate.z << endl;

		pixel_coordinate =
			GetPixelCoordinate(cam, 
				{ 0, cam.image_size.width });
		cout << "pixel_coordinate: x="
			<< pixel_coordinate.x << ", y="
			<< pixel_coordinate.y << ", z="
			<< pixel_coordinate.z << endl;

		pixel_coordinate =
			GetPixelCoordinate(cam,
				{ cam.image_size.height, 0});
		cout << "pixel_coordinate: x="
			<< pixel_coordinate.x << ", y="
			<< pixel_coordinate.y << ", z="
			<< pixel_coordinate.z << endl;

		pixel_coordinate =
			GetPixelCoordinate(cam,
				{ cam.image_size.height,
				cam.image_size.width });
		cout << "pixel_coordinate: x="
			<< pixel_coordinate.x << ", y="
			<< pixel_coordinate.y << ", z="
			<< pixel_coordinate.z << endl;

		pixel_coordinate =
			GetPixelCoordinate(cam,
				{ 1124, 789});
		cout << "pixel_coordinate: x="
			<< pixel_coordinate.x << ", y="
			<< pixel_coordinate.y << ", z="
			<< pixel_coordinate.z << endl;
	}


}