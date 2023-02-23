#include "Profile.h"
#include "Rotate.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"
#include "Transform.h"
#include "TestFunctions.h"
#include "GetCamera.h"
#include "WriteReadCamera.h"
#include "CreateTrajectory.h"

using namespace std;

int main()
{
	double pitch = 3.141592 / 3;
	double hfov = 3.141592 / 4;
	ImageSize img_size = { 1000, 2000 };
	auto trajectory = CreateTackTrajectory(
		{ 25, 50 },
		{ 70, 120 },
		{ 0.1, 0.2 },
		pitch,
		50,
		hfov,
		img_size	
	);

	ReferenceImage ref_img(
		cv::imread("C:/Users/Mi/source/repos/Diploma/Diploma/resources/img.tif", cv::IMREAD_COLOR),
		0.02
	);

	string dir_path = "C:/Users/Mi/source/repos/Diploma/Diploma/resources/created_images3";

	CreateSetOfImages(
		ref_img,
		trajectory.first,
		trajectory.second,
		hfov,
		img_size,
		dir_path
	);

	ConcatenateImagesInDirectory(dir_path, 0.05);
}


//Debug
//imread: 1774
//GetTransformedImage : 3789
//cv::imwrite : 176
//total : 5125

//Relea
//GetTransformedImage : 1338
//cv::imwrite : 73
//total : 1745

//string img_path = "C:/Users/Mi/Pictures/Blender/sequential_big/x-1000y0z1000r0p60y0.png";
//{
//	LOG_DURATION("imread");
//	cv::Mat img = cv::imread("C:/Users/Mi/Pictures/Blender/sequential_big/x-1000y0z1000r0p60y0.png", cv::IMREAD_COLOR);
//}
//LOG_DURATION("total");
//
//cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
//
//Camera cam =
//{
//	img,
//	Coordinate3D{-1000, 0, 1000},
//	EulerAngles{0, 3.141592 / 3, 0},
//	MatrixSize{0.2160, 0.3840},
//	FieldOfView{0.39, 0.69}
//};
//
//cv::Mat new_img;
//{
//	LOG_DURATION("GetTransformedImage");
//	new_img = TransformImage(cam, 1000);
//}
//
//{
//	LOG_DURATION("cv::imwrite");
//	cv::imwrite("C:/Users/Mi/Pictures/Blender/res/res.png", new_img);
//}