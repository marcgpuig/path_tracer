#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:

  using value_type = double;

  vec3() : u{0.0, 0.0, 0.0} {}
  vec3(const value_type &u0, const value_type &u1, const value_type &u2)
  : u{u0, u1, u2} {}

  ~vec3() = default;

  inline value_type x() const { return u[0]; }
  inline value_type y() const { return u[1]; }
  inline value_type z() const { return u[2]; }
  inline value_type r() const { return u[0]; }
  inline value_type g() const { return u[1]; }
  inline value_type b() const { return u[2]; }

  inline const vec3& operator+() const { return *this; }
  inline vec3 operator-() const { return vec3(-u[0], -u[1], -u[2]); }
  inline value_type operator[](int i) const { return u[i]; }
  inline value_type& operator[](int i) { return u[i]; }

  inline vec3& operator+=(const vec3 &o)
  {
    u[0] += o.u[0];
    u[1] += o.u[1];
    u[2] += o.u[2];
    return *this;
  }

  inline vec3& operator-=(const vec3 &o)
  {
    u[0] -= o.u[0];
    u[1] -= o.u[1];
    u[2] -= o.u[2];
    return *this;
  }

  inline vec3& operator*=(const vec3 &o)
  {
    u[0] *= o.u[0];
    u[1] *= o.u[1];
    u[2] *= o.u[2];
    return *this;
  }

  inline vec3& operator/=(const vec3 &o)
  {
    u[0] /= o.u[0];
    u[1] /= o.u[1];
    u[2] /= o.u[2];
    return *this;
  }

  inline vec3& operator*=(const value_type v)
  {
    u[0] *= v;
    u[1] *= v;
    u[2] *= v;
    return *this;
  }

  inline vec3& operator/=(const value_type v)
  {
    value_type inv_v = 1.0 / v;
    u[0] *= inv_v;
    u[1] *= inv_v;
    u[2] *= inv_v;
    return *this;
  }

  inline value_type lenght() const
  {
    return sqrt(u[0] * u[0] + u[1] * u[1] + u[0] * u[0]);
  }

  inline value_type squared_lenght() const
  {
    return u[0] * u[0] + u[1] * u[1] + u[0] * u[0];
  }

  inline void make_unit_vector()
  {
    value_type k = 1.0 / lenght();
    u[0] *= k;
    u[1] *= k;
    u[2] *= k;
  }

  value_type u[3];
};

inline std::istream& operator>>(std::istream &is, vec3 &t) {
    is >> t.u[0] >> t.u[1] >> t.u[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) {
    os << t.u[0] << " " << t.u[1] << " " << t.u[2];
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
  return v0.u[0] * v1.u[0] + v0.u[1] * v1.u[1] + v0.u[2] * v1.u[2];
}

inline vec3 cross(const vec3 &v0, const vec3 &v1)
{
  return vec3(
      v0.u[1] * v1.u[2] - v0.u[2] * v1.u[1],
    -(v0.u[0] * v1.u[2] - v0.u[2] * v1.u[0]),
      v0.u[0] * v1.u[1] - v0.u[1] * v1.u[0]);
}

#endif
