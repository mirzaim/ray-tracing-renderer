#ifndef COLOR_H
#define COLOR_H

#include "utility.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
  int ir = static_cast<int>(std::round(255 * pixel_color.x()));
  int ig = static_cast<int>(std::round(255 * pixel_color.y()));
  int ib = static_cast<int>(std::round(255 * pixel_color.z()));

  out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif