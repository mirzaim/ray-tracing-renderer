#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "utility.h"

int main() {
  // World
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1.5);
  auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

  hittable_list world;
  world.add(make_shared<sphere>(point3(0, -50.5, 1), 50, material_ground));
  world.add(make_shared<sphere>(point3(0, 0, 1.3), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1, 0, 1), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-1, 0, 1), 0.4, material_bubble));
  world.add(make_shared<sphere>(point3(1, 0, 1), 0.5, material_right));

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width = 400;
  cam.samples_per_pixel = 20;
  cam.max_depth = 50;

  cam.vfov = 90;

  cam.render(world);
}