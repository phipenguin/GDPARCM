#pragma once
#include "Vec3.h"
#include <iostream>

class Color : public Vec3
{
public:
	void write_color(std::ostream &out, Vec3 pixel_color) {
		// Write the translated [0,255] value of each Color component.
		out << static_cast<int>(255.999 * pixel_color.x()) << ' '
			<< static_cast<int>(255.999 * pixel_color.y()) << ' '
			<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
	}
};
