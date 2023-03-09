#include "RaytraceThread.h"

RaytraceThread::RaytraceThread(int id, int image_height, int l_row, int u_row)
{
	this->id = id;
	this->l_row = l_row;
	this->u_row = u_row;
	this->l_col = 0;
	this->u_col = image_height;
}

RaytraceThread::~RaytraceThread()
{
}

void RaytraceThread::setAttributes(Camera* cam, HittableList world, int depth, int ray_samples_per_pixel,
	int image_width, int image_height)
{
	this->cam = cam;
	this->world = world;
	this->depth = depth;
	this->ray_samples_per_pixel = ray_samples_per_pixel;
	this->image_height = image_height;
	this->image_width = image_width;
}

void RaytraceThread::setImage(RTImage* image)
{
	this->image = image;
}

color RaytraceThread::ray_color(const Ray& r, const Hittable& world, int depth)
{
	hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        Ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

void RaytraceThread::run()
{
    is_running = true;

	for (int j = this->u_col-1; j >= this->l_col; --j)
    {
        for (int i = this->l_row; i < this->u_row; ++i)
        {
        	color pixel_color(0, 0, 0);

            for (int s = 0; s < this->ray_samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (this->image_width-1);
                auto v = (j + random_double()) / (this->image_height-1);
                Ray r = this->cam->get_ray(u, v);
                pixel_color += RaytraceThread::ray_color(r, this->world, this->depth);
            }

        	this->image->setPixel(i, j, pixel_color.x(), pixel_color.y(), pixel_color.z(), this->ray_samples_per_pixel);
        }
    }

    is_running = false;
}
