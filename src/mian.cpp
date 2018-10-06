#include <iostream>
#include <cstdint>
#include <memory>

#include "ray.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

const int32_t WIDTH = 400;
const int32_t HEIGHT = 200;
const uint8_t CHANNELS = 3;
const int64_t TOTAL_BYTES = WIDTH * HEIGHT * CHANNELS;

int64_t image_pixel(const int32_t &x, const int32_t &y)
{
  return ((HEIGHT - 1 - y) * WIDTH + x) * CHANNELS;
}

double hit_sphere(const vec3 &center, double radius, const ray &r)
{
  // sphere on p(x, y, z):
  // r*r = x*x + y*y + z*z
  // sphere on center C(cx, cy, cz) on p(x, y, z):
  // r*r = (x-cx)*(x-cx) + (y-cy)*(y-cy) + (z-cz)*(z-cz)
  // using vec3 we can solve it like this:
  // dot(p-C, p-C) = r*r
  // see if a ray (p(t) = A + t*B) collides with sphere:
  // dot(p(t)-C, p(t)-C) = r*r
  // dot((A + t*B)-C, (A + t*B)-C) = r*r
  vec3 oc = r.origin() - center;
  double a = dot(r.direction(), r.direction());
  double b = 2.0 * dot(oc, r.direction());
  double c = dot(oc, oc) - radius * radius;
  double discrim = b * b - 4 * a * c;
  if (discrim < 0)
  {
    return -1.0;
  }
  else
  {
    return (-b - sqrt(discrim)) / (2.0 * a);
  }
}

// Blends white and blue depending on the height of the y coord
vec3 color(const ray &r)
{
  vec3 sphere_pos(0,0,-1);
  double t = hit_sphere(sphere_pos, 0.5, r);
  if (t > 0.0)
  {
    vec3 N = unit_vector(r.point_at_parameter(t) - sphere_pos);
    return .5 * vec3(N.x()+1, N.y()+1, N.z()+1);
  }
  // unit vector -1.0 < uint_direction < 1.0
  vec3 uint_direction = unit_vector(r.direction());
  // normalization 0.0 < t < 1.0
  t = 0.5 * (uint_direction.y() + 1.0);
  // t = 1.0 = blue | t = 0.0 = white
  return (1.0 - t) * vec3::ones() + t*vec3(0.5, 0.7, 1.0);
}

int main(int argc, char const *argv[])
{
  auto buffer = std::make_unique<uint8_t[]>(TOTAL_BYTES);

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin = vec3::zeros();

  for (int y = 0; y < HEIGHT; ++y)
  {
    for (int x = 0; x < WIDTH; ++x)
    {
      double u = double(x) / double(WIDTH);
      double v = double(y) / double(HEIGHT);

      ray r(origin, lower_left_corner + u*horizontal + v*vertical);

      vec3 col = color(r);

      buffer[image_pixel(x, y) + 0] = int(255.99 * col.r());
      buffer[image_pixel(x, y) + 1] = int(255.99 * col.g());
      buffer[image_pixel(x, y) + 2] = int(255.99 * col.b());
    }
  }

  std::cout << "Saving image..." << std::endl;
  stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, buffer.get(), 0);

  return 0;
}
