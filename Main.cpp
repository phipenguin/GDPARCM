#include "RTWeekend.h"

#include "Color.h"
//#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "RTImage.h"
#include "RaytraceThread.h"

#include <vector>
#include <iostream>

HittableList random_scene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -51; a < 51; a++) {
        for (int b = -51; b < 51; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	auto material4 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(point3(-8, 1, 0), 1.0, material4));

    return world;
}

int main()
{

    // Image

	//const auto aspect_ratio = 3.0 / 2.0;
	const auto aspect_ratio = 1.0;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;
    const int number_of_cores = 24;

    // World

    auto world = random_scene();

    // Camera

    point3 lookfrom(13,2,3);
	point3 lookat(0,0,0);
	Vec3 vup(0,1,0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    cv::String file_name = "D:/Apps/Github/GDPARCM/ImageRender.png";

    std::vector<RaytraceThread*> rt_cores;
    const int width_window = rint(image_width / number_of_cores);

    int l_row = 0;
    int u_row = width_window;

    RTImage* image = new RTImage(image_width, image_height);

    for (int i = 0; i < number_of_cores; i ++)
    {
	    std::cout << " " << l_row << " " << u_row << std::endl;

        RaytraceThread* rt_compute = new RaytraceThread(i, image_height, l_row, u_row);
        rt_compute->setAttributes(&cam, world, max_depth, samples_per_pixel, image_width, image_height);
        rt_compute->setImage(image);
        rt_compute->start();

        rt_cores.push_back(rt_compute);

        l_row += width_window;
        u_row += width_window;
    }

    bool standby = true;

    while (standby)
    {
	    for (int i = 0; i < number_of_cores; i ++)
	    {
		    standby = false;
            if (rt_cores[i]->is_running)
            {
	            standby = true;
                break;
            }
	    }
    }

    image->saveImage(file_name);

    std::cerr << "\nDone.\n";
}