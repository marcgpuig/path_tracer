#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:

  using value_type = double;

  vec3() : c{0.0, 0.0, 0.0} {}
  vec3(const value_type &u0, const value_type &u1, const value_type &u2)
  : c{u0, u1, u2} {}

  ~vec3() = default;

  static vec3 zeros() { return vec3(); }
  static vec3 ones()  { return vec3(1.0, 1.0, 1.0); }

  value_type x() const { return c[0]; }
  value_type y() const { return c[1]; }
  value_type z() const { return c[2]; }
  value_type r() const { return c[0]; }
  value_type g() const { return c[1]; }
  value_type b() const { return c[2]; }

  const vec3 &operator+()       const { return *this; }
  vec3        operator-()       const { return vec3(-c[0], -c[1], -c[2]); }
  value_type  operator[](int i) const { return c[i]; }
  value_type &operator[](int i)       { return c[i]; }

  vec3 &operator+=(const vec3 &o)
  {
    c[0] += o.c[0];
    c[1] += o.c[1];
    c[2] += o.c[2];
    return *this;
  }

  vec3 &operator-=(const vec3 &o)
  {
    c[0] -= o.c[0];
    c[1] -= o.c[1];
    c[2] -= o.c[2];
    return *this;
  }

  vec3 &operator*=(const vec3 &o)
  {
    c[0] *= o.c[0];
    c[1] *= o.c[1];
    c[2] *= o.c[2];
    return *this;
  }

  vec3 &operator/=(const vec3 &o)
  {
    c[0] /= o.c[0];
    c[1] /= o.c[1];
    c[2] /= o.c[2];
    return *this;
  }

  vec3 &operator*=(const value_type v)
  {
    c[0] *= v;
    c[1] *= v;
    c[2] *= v;
    return *this;
  }

  vec3 &operator/=(const value_type v)
  {
    value_type inv_v = 1.0 / v;
    c[0] *= inv_v;
    c[1] *= inv_v;
    c[2] *= inv_v;
    return *this;
  }

  value_type lenght() const
  {
    return sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
  }

  value_type squared_lenght() const
  {
    return c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
  }

  void make_unit_vector()
  {
    value_type k = 1.0 / lenght();
    c[0] *= k;
    c[1] *= k;
    c[2] *= k;
  }

  value_type c[3]; // coordinates
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
    is >> t.c[0] >> t.c[1] >> t.c[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
    os << t.c[0] << " " << t.c[1] << " " << t.c[2];
    return os;
}

inline vec3 operator+(vec3 v0, const vec3 &v1)
{
 return v0 += v1;
}

inline vec3 operator-(vec3 v0, const vec3 &v1)
{
 return v0 -= v1;
}

inline vec3 operator*(vec3 v0, const vec3 &v1)
{
 return v0 *= v1;
}

inline vec3 operator/(vec3 v0, const vec3 &v1)
{
 return v0 /= v1;
}

inline vec3 operator*(vec3 v0, const vec3::value_type &v)
{
 return v0 *= v;
}

inline vec3 operator*(const vec3::value_type &v, vec3 v0)
{
 return v0 *= v;
}

inline vec3 operator/(vec3 v0, const vec3::value_type &v)
{
 return v0 /= v;
}

inline vec3 unit_vector(vec3 v)
{
  return v / v.lenght();
}

inline vec3::value_type dot(const vec3 &v0, const vec3 &v1)
{
  return v0.c[0] * v1.c[0] + v0.c[1] * v1.c[1] + v0.c[2] * v1.c[2];
}

inline vec3 cross(const vec3 &v0, const vec3 &v1)
{
  return vec3(
      v0.c[1] * v1.c[2] - v0.c[2] * v1.c[1],
    -(v0.c[0] * v1.c[2] - v0.c[2] * v1.c[0]),
      v0.c[0] * v1.c[1] - v0.c[1] * v1.c[0]);
}

#endif // !VEC3_H
