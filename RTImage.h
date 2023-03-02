#pragma once
#include <vector>
#include "opencv2/core.hpp"

class RTImage
{
public:
	RTImage(const int image_width, const int image_height);
	void setPixel(int x, int y, float r, float g, float b, int samples_per_pixel);
	//std::vector <std::vector<Color>> returnImage();
	void saveImage(cv::String &file_name) const;

private:
	//std::vector<std::vector<Color>> pixels;
	std::unique_ptr<cv::Mat> pixels;
	int image_width;
	int image_height;
};