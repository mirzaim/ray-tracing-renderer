#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
 private:
  /* data */
 public:
  virtual ~material() = default;

  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       color& attenuation, ray& scattered) const {
    return false;
  }
};

class lambertian : public material {
 private:
  color albedo;

 public:
  lambertian(const color& albedo) : albedo(albedo) {};

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
               ray& scattered) const override {
    auto scatter_dir = rec.normal + random_unit_vector();

    if (scatter_dir.near_zero()) scatter_dir = rec.normal;

    scattered = ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
  }
};

class metal : public material {
 private:
  color albedo;
  double fuzz;

 public:
  metal(const color& albedo, double fuzz)
      : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {};

  bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
               ray& scattered) const override {
    auto reflected = reflect(r_in.diraction(), rec.normal);
    reflected = unit(reflected) + fuzz * random_unit_vector();
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(reflected, rec.normal) > 0);
  }
};

#endif