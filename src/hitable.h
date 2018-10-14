#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

class material;

struct hit_record
{
  // distance
  double t;
  // position
  vec3 p;
  // normal
  vec3 normal;
  material *mat = nullptr;
};

class hitable
{
public:
  virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif // !HITABLE_H
