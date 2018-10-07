#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
public:
  camera()
  : origin(),
    lower_left_corner(-2.0, -1.0, -1.0), 
    horizontal(4.0, 0.0, 0.0),
    vertical(0.0, 2.0, 0.0) {}

  ray get_ray(double u, double v)
  {
    return ray(origin, lower_left_corner + u * horizontal + v * vertical);
  }

  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
};

#endif // !CAMERA_H