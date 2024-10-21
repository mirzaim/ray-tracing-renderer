#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "utility.h"

int main() {
  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, 1), 0.5));
  world.add(make_shared<sphere>(point3(0, -50.5, 1), 50));

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width = 400;
  cam.samples_per_pixel = 20;
  cam.max_depth = 50;

  cam.render(world);
}