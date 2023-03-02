#include "RTImage.h"
#include "RTWeekend.h"
#include "opencv2/opencv.hpp"

RTImage::RTImage(const int image_width, const int image_height)
{
	this->image_width = image_width;
	this->image_height = image_height;

	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->image_height, this->image_width, CV_8UC3));
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samples_per_pixel)
{
	//gamma correction
	float scale = 1.0f / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int rInt = static_cast<uchar>(256 * clamp(r, 0.0, 0.999));
	int gInt = static_cast<uchar>(256 * clamp(g, 0.0, 0.999));
	int bInt = static_cast<uchar>(256 * clamp(b, 0.0, 0.999));

	cv::Mat image_channels[3];
	cv::split(*this->pixels, image_channels);

	image_channels[0].at<uchar>(this->image_height - 1 - y, x) = bInt;
	image_channels[1].at<uchar>(this->image_height - 1 - y, x) = gInt;
	image_channels[2].at<uchar>(this->image_height - 1 - y, x) = rInt;

	cv::merge(image_channels, 3, *this->pixels);
}

void RTImage::saveImage(cv::String& file_name) const
{
	cv::imwrite(file_name, *this->pixels);
}
