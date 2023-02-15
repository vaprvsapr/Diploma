#include "WriteImage.h"

void WriteImage(
	const string& new_img_path, 
	const vector<vector<cv::Vec3b>>& data)
{
	size_t height = data.size();
	size_t width = data[0].size();

	cv::Mat img = cv::Mat::zeros(height, width, CV_8UC3);

	for (size_t i = 0; i < height; i++)
		for (size_t j = 0; j < width; j++)
		{
			img.at<cv::Vec3b>(i, j) = data[i][j];
		}

	cv::imwrite(new_img_path, img);
}