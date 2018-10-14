#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "random_engine.h"

#define PI 3.14159265359
#define HALF_PI 1.57079632679

vec3 random_in_unit_disk()
{
  vec3 p;
  do {
    p = 2.0 * vec3(dist(mt), dist(mt), 0) - vec3(1,1,0);
  } while (dot(p,p) >= 1.0);
  return p;
}

class camera
{
public:
  camera(vec3 pos, vec3 lookat, vec3 up, double vfov, double aspect, double aperture, double focus_dist)
    : lens_radius(aperture / 2)
  {
    double theta = vfov * PI / 180;
    double half_height = tan(theta / 2);
    double half_width = aspect * half_height;
    origin = pos;
    w = unit_vector(pos - lookat);
    u = unit_vector(cross(up, w));
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
  }

  ray get_ray(double s, double t)
  {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
  }

  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u, v, w;
  float lens_radius;
};

#endif // !CAMERA_H
