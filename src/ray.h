#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// p(t) = A + t*B
// Where Here ​p is a 3D position along a line in 3D.
class Ray
{
public:
  Ray() = default;
  Ray(const Vec3 &a, const Vec3 &b) : A(a), B(b) {}
  ~Ray() {}

  Vec3 origin() const    { return A; }
  Vec3 direction() const { return B; }
  Vec3 point_at_parameter(double t) const { return A + t * B; }

  Vec3 A;
  Vec3 B;
};

#endif // !RAY_H
