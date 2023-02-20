#include "Profile.h"
#include "Rotate.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"
#include "Transform.h"

using namespace std;

int main()
{
	string img_path = "C:/Users/Mi/Pictures/Blender/sequential_big/x-1000y0z1000r0p60y0.png";
	{
		LOG_DURATION("imread");
		cv::Mat img = cv::imread("C:/Users/Mi/Pictures/Blender/sequential_big/x-1000y0z1000r0p60y0.png", cv::IMREAD_COLOR);
	}
	LOG_DURATION("total");

	cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);

	Camera cam =
	{
		img,
		Coordinate3D{-1000, 0, 1000},
		EulerAngles{0, 3.141592 / 3, 0},
		MatrixSize{0.2160, 0.3840},
		FieldOfView{0.39, 0.69}
	};

	cv::Mat new_img;
	{
		LOG_DURATION("GetTransformedImage");
		new_img = GetTransformedImage(cam, 1000);
	}

	{
		LOG_DURATION("cv::imwrite");
		cv::imwrite("C:/Users/Mi/Pictures/Blender/res/res.png", new_img);
	}
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