#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

#include <memory>

class Sphere : public Hitable
{
public:
  Sphere() : center(), radius(0) {}
  Sphere(Vec3 pos, double r, std::shared_ptr<Material> m) : center(pos), radius(r), mat(std::move(m)) {}
  bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

  Vec3 center;
  double radius;
  std::shared_ptr<Material> mat;
};

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const
{
  // Formula for sphere on point p(x, y, z):
  //   x*x + y*y + z*z = r*r
  //
  // sphere with center C(cx, cy, cz) on point p(x, y, z):
  //   (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz) = r*r
  //
  // so:
  //   (p-C) * (p-C) = r*r
  //
  // using a vector we can solve it like this:
  //   dot(p-C, p-C) = r*r
  //
  // see if a ray (p(t) = A + t*B) collides with sphere:
  //   dot(p(t)-C, p(t)-C) = r*r
  //   dot((A + t*B)-C, (A + t*B)-C) = r*r
  //   ((A + t*B)-C)*((A + t*B)-C) = r*r
  //
  // discriminant on ax^2+bx+c=0 is b^2-4ac
  // if the discriminant == 0, it has one solution,
  // otherwhise if it is < 0 it has no solition
  // and if it is > 0, it has 2 solutions.

  Vec3 oc = r.origin() - center;
  double a = dot(r.direction(), r.direction());
  double b = dot(oc, r.direction());
  double c = dot(oc, oc) - radius * radius;
  double discrim = b * b - a * c;
  if(discrim > 0)
  {
    double temp = (-b - sqrt(b*b-a*c)) / a;
    if(temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat = mat;
      return true;
    }
    temp = (-b + sqrt(b*b-a*c)) / a;
    if(temp < t_max && temp > t_min)
    {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.mat = mat;
      return true;
    }
  }
  return false;
}

#endif // !SPHERE_H
