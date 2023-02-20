#include "Profile.h"
#include "Rotate.h"
#include "GetPixelCoordinate.h"
#include "Projection.h"
#include "Transform.h"

using namespace std;

int main()
{

	cv::Mat img = cv::imread("C:/Users/Mi/Pictures/Blender/sequential_big/x-1000y0z1000r0p60y0.png", cv::IMREAD_COLOR);

	Camera cam =
	{
		img,
		Coordinate3D{-1000, 0, 1000},
		EulerAngles{0, 3.141592 / 3, 0},
		MatrixSize{0.2160, 0.3840},
		FieldOfView{0.39, 0.69}
	};

	cout << cam.focal_length << endl;

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