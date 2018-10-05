#include <iostream>
#include <cstdint>

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

bool hit_sphere(const vec3 &center, double radius, const ray &r)
{
  vec3 oc = r.origin() - center;
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(oc, r.direction());
  float c = dot(oc, oc) - radius * radius;
  float discrim = b * b - 4 * a * c;
  return discrim > 0;
}

// Blends white and blue depending on the height of the y coord
vec3 color(const ray &r)
{
  if (hit_sphere(vec3(0,0,-1), 0.5, r))
    return vec3(1,0,1);
  // unit vector -1.0 < uint_direction < 1.0
  vec3 uint_direction = unit_vector(r.direction());
  // normalization 0.0 < t < 1.0
  double t = 0.5 * (uint_direction.y() + 1.0);
  // t = 1.0 = blue | t = 0.0 = white
  return (1.0 - t) * vec3::ones() + t*vec3(0.5, 0.7, 1.0);
}

int main(int argc, char const *argv[])
{
  uint8_t buffer[TOTAL_BYTES];

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
  stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, buffer, 0);

  return 0;
}
