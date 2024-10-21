#ifndef VEC3_H
#define VEC3_H

#include "utility.h"

class vec3 {
 private:
  double e[3];

 public:
  vec3() : e{0, 0, 0} {};
  vec3(double e0, double e1, double e2) : e{e0, e1, e2} {};

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  vec3& operator+=(const vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  vec3& operator*=(double v) {
    e[0] *= v;
    e[1] *= v;
    e[2] *= v;
    return *this;
  }

  vec3& operator/=(double v) { return *this *= 1 / v; }

  double length() const { return std::sqrt(length_squared()); }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  bool near_zero() const {
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }

  static vec3 random() {
    return vec3(random_double(), random_double(), random_double());
  }

  static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
  return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
  return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
  return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator*(double t, const vec3& v) {
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t) {
  return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator/(const vec3& v, double t) { return 1 / t * v; }

inline double dot(const vec3& v1, const vec3& v2) {
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
  return vec3(v1.y() * v2.z() - v1.z() * v2.y(),
              v1.z() * v2.x() - v1.x() * v2.z(),
              v1.x() * v2.y() - v1.y() * v2.x());
}

inline vec3 unit(const vec3& v) { return v / v.length(); }

inline vec3 random_unit_vector() {
  while (true) {
    auto p = vec3::random(-1, 1);
    auto lensq = p.length_squared();
    if (1e-160 < lensq && lensq <= 1) return p / sqrt(lensq);
  }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
  vec3 on_unit_sphere = random_unit_vector();
  return (dot(normal, on_unit_sphere) > 0.0) ? on_unit_sphere : -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
  auto r_out_perp = (dot(-uv, n) * n + uv) * etai_over_etat;
  auto r_out_parallel =
      -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_parallel + r_out_perp;
}

#endif