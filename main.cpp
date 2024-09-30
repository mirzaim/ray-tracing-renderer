#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "utility.h"

color ray_color(const ray& r, hittable& world) {
  hit_record hit_r{};
  if (world.hit(r, interval(0, infinity), hit_r))
    return 0.5 * (hit_r.normal + color(1, 1, 1));

  double a = 0.5 * (unit(r.diraction()).y() + 1.0);
  return color(0.5, 0.7, 1.0) * a + (1 - a) * color(1.0, 1.0, 1.0);
}

int main() {
  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, 1), 0.5));
  world.add(make_shared<sphere>(point3(0, -50.5, 1), 50));

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width = 400;

  cam.render(world);
}