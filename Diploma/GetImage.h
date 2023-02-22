#pragma once

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "Structures.h"

using namespace std;

Camera GetImage(
	const cv::Mat& image,				// референсное изображение
	const double& spatial_resolution,	// в метрах
	const Coordinate3D& position,		// позиция камеры
	const EulerAngles& orientation,		// ориентация камеры
	const double& horizontal_field_of_view,
	const ImageSize& image_size
)
{
	
}
