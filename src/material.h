#ifndef MATERIAL_H
#define MATERIAL_H

struct hit_record;

#include "ray.h"
#include "hitable.h"
#include "random_engine.h"

#include <algorithm>

vec3 random_in_unit_sphere()
{
  vec3 p;
  do {
    p = 2.0 * vec3(dist(mt), dist(mt), dist(mt)) - vec3::ones();
  } while (p.squared_length() >= 1.0);
  return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
  return v - 2 * dot(v, n) * n;
}

double schlick(double cosine, double ref_index)
{
  float r0 = (1 - ref_index) / (1 + ref_index);
  r0 = r0*r0;
  return r0 + (1-r0) * pow((1 - cosine), 5);
}

bool refract(const vec3 &v, const vec3 &n, double ni_over_nt, vec3 &refracted)
{
  vec3 uv = unit_vector(v);
  double dt = dot(uv, n);
  double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
  if (discriminant > 0)
  {
    refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    return true;
  }
  else
  {
    return false;
  }
}

double clamp01(double f) { return (f > 1) ? 1 : (f < 0) ? 0 : f; }

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
  bool scatter(const ray &r_in, const hit_record &rec,
    vec3 &attenuation, ray &scattered) const override
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
  metal(const vec3 &alb, double f) : albedo(alb), fuzz(clamp01(f)) {}
  bool scatter(const ray &r_in, const hit_record &rec,
    vec3 &attenuation, ray &scattered) const override
  {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

  vec3 albedo;
  double fuzz;
};

class dielectric : public material
{
public:
  dielectric (float ri) : ref_index(ri) {}
  bool scatter(const ray& r_in, const hit_record &rec,
    vec3 &attenuation, ray &scattered) const override
  {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0, 1.0, 1.0);
    vec3 refracted;
    double reflect_prob;
    double cosine;
    if(dot(r_in.direction(), rec.normal) > 0)
    {
      outward_normal = -rec.normal;
      ni_over_nt = ref_index;
      cosine = ref_index * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    else
    {
      outward_normal = rec.normal;
      ni_over_nt = 1.0 / ref_index;
      cosine = - dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
    {
      reflect_prob = schlick(cosine, ref_index);
    }
    else
    {
      scattered = ray(rec.p, reflected);
      reflect_prob = 1.0;
    }
    if (dist(mt) < reflect_prob)
    {
      scattered = ray(rec.p, reflected);
    }
    else
    {
      scattered = ray(rec.p, refracted);
    }
    return true;
  }
  float ref_index;
};

#endif // !MATERIAL_H
