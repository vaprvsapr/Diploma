#include "Profile.h"
#include "Rotate.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"
#include "Transform.h"
#include "TestFunctions.h"
#include "GetCamera.h"
#include "WriteCamera.h"
#include "ReadCamera.h"
#include "CreateTrajectory.h"
#include "CreateSetOfImagesInDir.h"
#include "GetNoisy.h"

using namespace std;

int main()
{
	//double pitch = 3.141592 / 3;
	//double hfov = 3.141592 / 4;
	//ImageSize img_size = { 1080, 1920 };
	//auto trajectory = CreateTackTrajectory(
	//	{ 0, 0 },
	//	{ 100, 100 },
	//	{ 0.3, 0.3 },
	//	pitch,
	//	50,
	//	hfov,
	//	img_size
	//);


	////auto trajectory = CreateTrajectoryForGeoscan201(
	////	{ 5, 5 },
	////	{ 50, 100 },
	////	{ 0.2, 0.2 },
	////	hfov,
	////	img_size,
	////	11,
	////	{ 0.02 }
	////);

	//string dir_path = "C:/Users/Mi/Pictures/resources/agisoft/2";
	//ReferenceImage ref_img(
	//		cv::imread("C:/Users/Mi/Pictures/unnamed.png",
	//			cv::IMREAD_COLOR),
	//		0.1
	//	);
	////	auto noisy_coordinates =
	////	GetNoisyCoordinates(trajectory.first, 
	////		{ 0, 0, 0 }, { 2, 2, 5 });
	////	auto noisy_orientations =
	////	GetNoisyOrientations(trajectory.second,
	////		{ 0, 0, 0 }, 
	////		{ 3.141592 / 180 * 2, 3.141592 / 180 * 2, 3.141592 / 180 * 2 });
	//	CreateSetOfImagesInDir(
	//		ref_img,
	//		trajectory.first,
	//		trajectory.second,
	//		hfov,
	//		img_size,
	//		dir_path
	//	);
	////}
	string dir_path = "D:/important/Unigine/Storage/orientations/MissionPlanner/test_super_resolution_set";
	ConcatenateImagesInDirectoryReadTrajectoryFromFile(dir_path, 0.1);

	auto cameras = ReadCamerasFromDirectory(dir_path);
	cout << "Pixel overlap:\n";
	//CalculatePixelOverlapBetweenSetOfImages(cameras);
	cout << "Area overlap:\n";
	CalculateAreaOverlapBetweenSetOfImages(cameras);
}
