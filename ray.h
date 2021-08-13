#ifndef RAY_H
#define RAY_H

#include "utility.h"

class ray {
 private:
  vec3 orig;
  vec3 dir;

 public:
  ray() {}
  ray(const vec3& origin, const vec3& direction)
      : orig(origin), dir(direction) {}

  const point3& origin() const { return orig; }
  const point3& diraction() const { return dir; }

  point3 at(double t) const { return orig + t * dir; }
};

#endif