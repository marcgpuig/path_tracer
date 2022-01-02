#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "random_engine.h"

#define PI 3.14159265359
#define HALF_PI 1.57079632679

Vec3 random_in_unit_disk()
{
  Vec3 p;
  do {
    p = 2.0 * Vec3(dist(mt), dist(mt), 0) - Vec3(1,1,0);
  } while (dot(p,p) >= 1.0);
  return p;
}

class Camera
{
public:
  Camera(Vec3 pos, Vec3 lookat, Vec3 up, double vfov, double aspect, double aperture, double focus_dist)
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

  Ray get_ray(double s, double t)
  {
    Vec3 rd = lens_radius * random_in_unit_disk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
  }

  Vec3 origin;
  Vec3 lower_left_corner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 u, v, w;
  float lens_radius;
};

#endif // !CAMERA_H
