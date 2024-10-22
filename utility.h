#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double random_double(double min, double max) {
  // Returns a random real in [min,max).
  return min + (max - min) * random_double();
}

void print_progress(float progress, std::ostream& outp) {
  int bar_width = 70;
  outp << "[";
  int pos = bar_width * progress;
  for (int i = 0; i < bar_width; ++i) {
    if (i < pos)
      outp << "=";
    else if (i == pos)
      outp << ">";
    else
      outp << " ";
  }
  outp << "] " << int(progress * 100.0) << " %\r";
  outp.flush();
}

#include "vec3.h"
#include "color.h"
#include "interval.h"
#include "ray.h"

#endif