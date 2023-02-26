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
#include "GetSetOfImages.h"

using namespace std;

int main()
{
	double pitch = 3.141592 / 4;
	double hfov = 3.141592 / 4;
	ImageSize img_size = { 1000, 2000 };
	auto trajectory = CreateTackTrajectory(
		{ 0, 0 },
		{ 200, 200 },
		{ 0.1, 0.1 },
		pitch,
		50,
		hfov,
		img_size	
	);

	ReferenceImage ref_img(
		cv::imread("C:/Users/Mi/Pictures/resources/img.tif", cv::IMREAD_COLOR),
		0.02
	);

	string dir_path = "C:/Users/Mi/Pictures/resources/created_images2";

	GetSetOfImages(
		ref_img,
		trajectory.first,
		trajectory.second,
		hfov,
		img_size,
		dir_path
	);

	ConcatenateImagesInDirectoryDev(dir_path, 0.1);
}
