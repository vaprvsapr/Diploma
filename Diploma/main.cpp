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
	double pitch = 3.141592 / 2;
	double hfov = 3.141592 / 180 * 40;
	ImageSize img_size = { 1000, 2000 };
	auto trajectory = CreateTackTrajectory(
		{ 50, 50 },
		{ 100, 100 },
		{ 0.3, 0.3 },
		pitch,
		50,
		hfov,
		img_size	
	);

	string dir_path = "C:/Users/Mi/Pictures/resources/noisy_coord2";
	{
		ReferenceImage ref_img(
			cv::imread("C:/Users/Mi/Pictures/resources/img.tif",
				cv::IMREAD_COLOR),
			0.02
		);


		auto noisy_coordinates =
			GetNoisyCoordinates(trajectory.first, 
				{ 0, 0, 0 }, { 5, 5, 5 });
		auto noisy_orientations =
			GetNoisyOrientations(trajectory.second,
				{ 0, 0, 0 }, { 0, 0, 0 });

		CreateSetOfImagesInDir(
			ref_img,
			noisy_coordinates,
			noisy_orientations,
			hfov,
			img_size,
			dir_path
		);
	}
	ConcatenateImagesInDirectoryDev(dir_path, 0.1);
}
