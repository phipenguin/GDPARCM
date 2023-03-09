#pragma once
#include "IETThread.h"
#include "Camera.h"
#include "HittableList.h"
#include "RTImage.h"
#include "Material.h"

class RaytraceThread : public IETThread
{
public:
	RaytraceThread(int id, int image_height, int l_row, int u_row);
	~RaytraceThread();

	void setAttributes(Camera* cam, HittableList world, int depth, int ray_samples_per_pixel, int image_width, int image_height);
	void setImage(RTImage* image);

	color ray_color(const Ray& r, const Hittable& world, int depth);

	void run() override;

	bool is_running;

private:
	int id;

	int l_row; int u_row;
	int l_col; int u_col;

	Camera* cam;
	HittableList world;
	RTImage* image;
	int depth;
	int ray_samples_per_pixel;
	int image_height;
	int image_width;
};