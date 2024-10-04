#ifndef COLOR_H
#define COLOR_H

#include "utility.h"

using color = vec3;

inline double linear_to_gamma(double linear_component) {
  return (linear_component > 0) ? std::sqrt(linear_component) : 0;
}

void write_color(std::ostream& out, const color& pixel_color) {
  int ir = static_cast<int>(std::round(255 * linear_to_gamma(pixel_color.x())));
  int ig = static_cast<int>(std::round(255 * linear_to_gamma(pixel_color.y())));
  int ib = static_cast<int>(std::round(255 * linear_to_gamma(pixel_color.z())));

  out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif