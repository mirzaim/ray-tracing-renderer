#ifndef CAMERA_H
#define CAMERA_H

#include <omp.h>

#include "hittable.h"
#include "material.h"

class camera {
 public:
  double aspect_ratio = 1.0;
  int img_width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  double vfov = 90;
  point3 lookfrom = point3(0, 0, 0);
  point3 lookat = point3(0, 0, 1);
  vec3 vup = vec3(0, 1, 0);

  void render(const hittable& world) {
    initialize();

    int total_pixels = img_height * img_width;
    int pixel_count = 0, prev_report = 0;

    color* pixel_colors = new color[total_pixels];

    // Render
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < img_height; i++) {
      for (int j = 0; j < img_width; j++) {
        color pixel_color = color(0, 0, 0);
        for (auto s = 0; s < samples_per_pixel; s++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world, max_depth);
        }
        pixel_color /= samples_per_pixel;
        pixel_colors[i * img_width + j] = pixel_color;

        #pragma omp atomic
        ++pixel_count;

        if ((omp_get_thread_num() == 0) && (pixel_count > prev_report + 500)) {
          std::cerr << pixel_count << ' ' << total_pixels << '\n';
          prev_report = pixel_count;
        }
      }
    }

    std::cout << "P3\n" << img_width << " " << img_height << "\n255\n";
    for (int i = 0; i < img_height; i++) {
      for (int j = 0; j < img_width; j++) {
        write_color(std::cout, pixel_colors[i * img_width + j]);
      }
    }

    delete[] pixel_colors;
  }

 private:
  int img_height;

  vec3 u, v, w;
  vec3 pixel_delta_x;
  vec3 pixel_delta_y;

  vec3 pixel_loc_00;

  point3 camera_loc;
  double focal_length;

  void initialize() {
    // Image
    img_height = static_cast<int>(img_width / aspect_ratio);
    img_height = (img_height > 1) ? img_height : 1;

    camera_loc = lookfrom;

    // View point
    focal_length = (lookfrom - lookat).length();
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2 * h * focal_length;
    double viewport_width = viewport_height * double(img_width) / img_height;

    w = unit(lookfrom - lookat);
    u = unit(cross(w, vup));
    v = cross(w, u);

    vec3 viewport_x = viewport_width * u;
    vec3 viewport_y = viewport_height * v;

    pixel_delta_x = viewport_x / img_width;
    pixel_delta_y = viewport_y / img_height;

    pixel_loc_00 = camera_loc - focal_length * w - viewport_x / 2 -
                   viewport_y / 2 + 0.5 * (pixel_delta_x + pixel_delta_y);
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
    if (world.hit(r, interval(0.001, infinity), hit_r)) {
      ray scatter;
      color attenuation;
      if (hit_r.mat->scatter(r, hit_r, attenuation, scatter))
        return attenuation * ray_color(scatter, world, depth - 1);
      return color(0, 0, 0);
    }

    double a = 0.5 * (unit(r.diraction()).y() + 1.0);
    return color(0.5, 0.7, 1.0) * a + (1 - a) * color(1.0, 1.0, 1.0);
  }
};

#endif