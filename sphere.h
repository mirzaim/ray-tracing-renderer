#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "utility.h"

class sphere : public hittable {
 private:
  const point3& center;
  const double radius;

 public:
  sphere(const point3& center, double radius)
      : center(center), radius(radius) {};

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
    double a = dot(r.diraction(), r.diraction());
    double h = dot(r.diraction(), center - r.origin());
    double c = dot(center - r.origin(), center - r.origin()) - radius * radius;
    double discriminant = h * h - a * c;

    if (discriminant < 0) return false;

    double root = (h - std::sqrt(discriminant)) / a;
    if (!ray_t.surrounds(root)) {
      root = (h + std::sqrt(discriminant)) / a;
      if (!ray_t.surrounds(root)) return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    rec.set_face_normal(r, (rec.p - center) / radius);

    return true;
  };
};

#endif