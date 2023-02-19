//#include "ReadImage.h"
//
//vector<vector<cv::Vec3b>> ReadImage(const string& img_path)
//{
//	cv::Mat img = cv::imread(img_path, cv::IMREAD_COLOR);
//	size_t height = img.size().height;
//	size_t width = img.size().width;
//
//	vector<vector<cv::Vec3b>> data;
//	data.resize(height);
//
//	for (size_t i = 0; i < height; i++)
//	{
//		data[i].resize(width);
//		for (size_t j = 0; j < width; j++)
//		{
//			data[i][j] = img.at<cv::Vec3b>(i, j);
//		}
//	}
//	return data;
//}