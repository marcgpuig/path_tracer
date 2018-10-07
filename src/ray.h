#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// p(t) = A + t*B
// Where Here ​p is a 3D position along a line in 3D.
class ray
{
public:
  ray() = default;
  ray(const vec3 &a, const vec3 &b) : A(a), B(b) {}
  ~ray() {}

  vec3 origin() const    { return A; }
  vec3 direction() const { return B; }
  vec3 point_at_parameter(double t) const { return A + t * B; }

  vec3 A;
  vec3 B;
};

#endif // !RAY_H
