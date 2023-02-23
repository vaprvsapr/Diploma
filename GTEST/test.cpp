#include "pch.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "C:\Users\Mi\source\repos\Diploma\Diploma\Structures.h"
#include "C:\Users\Mi\source\repos\Diploma\Diploma\GetPixelCoordinate.h"

TEST(GetPixelCorners, GetPixelCorners) {
	Camera cam{
		cv::Mat::zeros({4, 5}, CV_8UC3),
		{0, 0, 0},
		{0, 0, 0},
		1.57
	};
	auto pixel_corners = GetPixelCorners(cam, { 1, 1 });
	EXPECT_EQ(make_tuple(0.0005, 0.0015),
		make_tuple(
			pixel_corners[0].y,
			pixel_corners[0].z)
	);
	EXPECT_EQ(make_tuple(0.0015, 0.0015),
		make_tuple(
			pixel_corners[1].y,
			pixel_corners[1].z)
	);
}