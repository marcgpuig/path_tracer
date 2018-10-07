#ifndef MATERIAL_H
#define MATERIAL_H

struct hit_record;

#include "ray.h"
#include "hitable.h"
#include "random_engine.h"

vec3 random_in_unit_sphere()
{
  vec3 p;
  do {
    p = 2.0 * vec3(dist(mt), dist(mt), dist(mt)) - vec3::ones();
  } while (p.squared_lenght() >= 1.0);
  return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
  return v - 2 * dot(v, n) * n;
}

class material
{
public:
  virtual bool scatter(const ray &ra_in, const hit_record &rec,
    vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material
{
public:
  lambertian(const vec3 &alb) : albedo(alb) {}
  virtual bool scatter(const ray &r_in, const hit_record &rec,
    vec3 &attenuation, ray &scattered) const
    {
      vec3 target = rec.p + rec.normal + random_in_unit_sphere();
      scattered = ray(rec.p, target - rec.p);
      attenuation = albedo;
      return true;
    }

  vec3 albedo;
};

class metal : public material
{
public:
  metal(const vec3 &alb) : albedo(alb) {}
  virtual bool scatter(const ray &r_in, const hit_record &rec,
    vec3 &attenuation, ray &scattered) const
    {
      vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
      scattered = ray(rec.p, reflected);
      attenuation = albedo;
      return (dot(scattered.direction(), rec.normal) > 0);
    }

  vec3 albedo;
};

#endif // !MATERIAL_H