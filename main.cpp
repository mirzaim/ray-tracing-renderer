#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "utility.h"

void scene_0(hittable_list& world, camera& cam) {
  // World
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = make_shared<dielectric>(1.5);
  auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
  auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

  world.add(make_shared<sphere>(point3(0, -50.5, 1), 50, material_ground));
  world.add(make_shared<sphere>(point3(0, 0, 1.3), 0.5, material_center));
  world.add(make_shared<sphere>(point3(-1, 0, 1), 0.5, material_left));
  world.add(make_shared<sphere>(point3(-1, 0, 1), 0.4, material_bubble));
  world.add(make_shared<sphere>(point3(1, 0, 1), 0.5, material_right));

  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width = 400;
  cam.samples_per_pixel = 20;
  cam.max_depth = 50;

  cam.vfov = 90;
  cam.lookfrom = point3(0, 0, 0);
  cam.lookat = point3(0, 0, 1);
  cam.vup = vec3(0, 1, 0);
}

void scene_1(hittable_list& world, camera& cam) {
  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  cam.aspect_ratio = 16.0 / 9.0;
  cam.img_width = 400;
  cam.samples_per_pixel = 20;
  cam.max_depth = 50;

  cam.vfov = 20;
  cam.lookfrom = point3(13, 2, 3);
  cam.lookat = point3(0, 0, 0);
  cam.vup = vec3(0, 1, 0);
}

int main(int argc, char* argv[]) {
  hittable_list world;
  camera cam;

  std::string input = (argc > 1) ? argv[1] : "0";

  if (input == "0") {
    scene_0(world, cam);
  } else if (input == "1") {
    scene_1(world, cam);
  } else {
    std::cerr << "Invalid input. Please provide a valid scene number."
              << std::endl;
    return 1;
  }

  cam.render(world);

  return 0;
}