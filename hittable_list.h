#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>

#include "hittable.h"
#include "utility.h"

class hittable_list : public hittable {
 private:
  std::vector<shared_ptr<hittable>> objects;

 public:
  hittable_list() {}
  hittable_list(shared_ptr<hittable> object) { add(object); }

  void add(shared_ptr<hittable> object) { objects.push_back(object); }
  void clear() { objects.clear(); }

  bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
    double closest = ray_t.max;
    hit_record temp_rec;
    bool hit = false;
    for (const auto& object : objects)
      if (object->hit(r, interval(ray_t.min, closest), temp_rec)) {
        hit = true;
        closest = temp_rec.t;
        rec = temp_rec;
      }
    return hit;
  }
};

#endif