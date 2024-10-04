#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

class camera {
 public:
  double aspect_ratio = 1.0;
  int img_width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  void render(const hittable& world) {
    initialize();

    // Render
    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";

    for (int i = 0; i < img_height; i++) {
      for (int j = 0; j < img_width; j++) {
        color pixel_color = color(0, 0, 0);
        for (auto s = 0; s < samples_per_pixel; s++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world, max_depth);
        }
        pixel_color /= samples_per_pixel;
        write_color(std::cout, pixel_color);
      }
    }
  }

 private:
  double viewport_height = 2.0;
  int img_height;

  vec3 pixel_delta_x;
  vec3 pixel_delta_y;

  vec3 pixel_loc_00;

  point3 camera_loc = point3(0, 0, 0);
  double focal_length = 1.0;

  void initialize() {
    // Image
    img_height = static_cast<int>(img_width / aspect_ratio);
    img_height = (img_height > 1) ? img_height : 1;

    // View point
    double const actual_aspect_ratio = double(img_width) / img_height;

    double viewport_width = viewport_height * actual_aspect_ratio;
    vec3 viewport_x = vec3(viewport_width, 0, 0);
    vec3 viewport_y = vec3(0, -viewport_height, 0);

    pixel_delta_x = viewport_x / img_width;
    pixel_delta_y = viewport_y / img_height;

    pixel_loc_00 = camera_loc + vec3(0, 0, focal_length) - viewport_x / 2 -
                   viewport_y / 2 + pixel_delta_x + pixel_delta_y;
  }

  ray get_ray(int i, int j) const {
    point3 pixel_ceter = pixel_loc_00 + i * pixel_delta_y + j * pixel_delta_x;
    point3 pixel_random = pixel_ceter +
                          (random_double() - 0.5) * pixel_delta_x +
                          (random_double() - 0.5) * pixel_delta_y;
    return ray(camera_loc, pixel_random - camera_loc);
  }

  color ray_color(const ray& r, const hittable& world, int depth) const {
    if (depth < 0) return color(0, 0, 0);

    hit_record hit_r{};
    if (world.hit(r, interval(0.001, infinity), hit_r))
      return 0.5 * (ray_color(ray(hit_r.p, hit_r.normal + random_unit_vector()),
                              world, depth - 1));

    double a = 0.5 * (unit(r.diraction()).y() + 1.0);
    return color(0.5, 0.7, 1.0) * a + (1 - a) * color(1.0, 1.0, 1.0);
  }
};

#endif