#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere : public hitable
{
public:
  sphere() : center(), radius(0) {}
  sphere(vec3 pos, double r, material *m) : center(pos), radius(r), mat(m) {}
  bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

  vec3 center;
  double radius;
  material *mat;
};

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
  // sphere on p(x, y, z):
  // x*x + y*y + z*z = r*r
  // sphere on center C(cx, cy, cz) on p(x, y, z):
  // (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz) = r*r
  // so:
  // (p-C) * (p-C) = r*r
  // using vec3 we can solve it like this:
  // dot(p-C, p-C) = r*r
  // see if a ray (p(t) = A + t*B) collides with sphere:
  // dot(p(t)-C, p(t)-C) = r*r
  // dot((A + t*B)-C, (A + t*B)-C) = r*r
  // ((A + t*B)-C)*((A + t*B)-C) = r*r
  // discriminant on ax^2+bx+c=0 is b^2-4ac
  // if discrim is 0 has one lolution,
  // if < 0 has no solition and if > 0 has 2 solutions

  vec3 oc = r.origin() - center;
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
