#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

#include <memory>

class Material;

struct HitRecord
{
  // distance
  double t;
  // position
  Vec3 p;
  // normal
  Vec3 normal;
  std::shared_ptr<Material> mat = nullptr;
};

class Hitable
{
public:
  virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
};

#endif // !HITABLE_H
