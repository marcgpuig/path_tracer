#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "rand_utils.h"

#include <iostream>
#include <cstdint>
#include <memory>
#include <limits>
#include <iomanip>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

const int32_t WIDTH = 400;
const int32_t HEIGHT = 200;
const uint8_t CHANNELS = 3;
const int64_t TOTAL_BYTES = WIDTH * HEIGHT * CHANNELS;
const uint16_t SAMPLES = 50;

int64_t image_pixel(const int32_t &x, const int32_t &y)
{
  return ((HEIGHT - 1 - y) * WIDTH + x) * CHANNELS;
}

vec3 random_in_unit_sphere()
{
  vec3 p;
  do {
    p = 2.0 * vec3(dist(mt), dist(mt), dist(mt)) - vec3::ones();
  } while (p.squared_lenght() >= 1.0);
  return p;
}

vec3 color(const ray &r, hitable *world)
{
  hit_record rec;
  // the 0.001 solves the "acne problem" in shadows
  if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec))
  {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    vec3 N = unit_vector(rec.normal);
    return .5 * color(ray(rec.p, target-rec.p), world);
  }
  else
  {
    // Blends white and blue depending on the height of the y coord
    // unit vector -1.0 < uint_direction < 1.0
    vec3 uint_direction = unit_vector(r.direction());
    // normalization 0.0 < t < 1.0
    double t = 0.5 * (uint_direction.y() + 1.0);
    // t = 1.0 = blue | t = 0.0 = white
    return (1.0 - t) * vec3::ones() + t*vec3(0.5, 0.7, 1.0);
  }
}

int main(int argc, char const *argv[])
{
  auto buffer = std::make_unique<uint8_t[]>(TOTAL_BYTES);

  const uint8_t object_num = 4;

  hitable *list[object_num];
  list[0] = new sphere(vec3(0,0,-1), 0.5);
  list[1] = new sphere(vec3(0,-100.5,-1), 100);
  list[2] = new sphere(vec3(0.4,-0.4,-0.9), .25);
  list[3] = new sphere(vec3(-1.0,0.0,-2.0), 1);
  hitable *world = new hitable_list(list, object_num);

  camera cam;

  std::cout << std::endl << "Rendering..." << std::endl;

  for (int y = 0; y < HEIGHT; ++y)
  {
    for (int x = 0; x < WIDTH; ++x)
    {
      vec3 col;
      for (uint16_t i = 0; i < SAMPLES; ++i)
      {
        double u = double(x + dist(mt)) / double(WIDTH);
        double v = double(y + dist(mt)) / double(HEIGHT);
        ray r = cam.get_ray(u, v);
        col += color(r, world);
      }
      col /= float(SAMPLES);
      col /= vec3(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));

      buffer[image_pixel(x, y) + 0] = int(255.99 * col.r());
      buffer[image_pixel(x, y) + 1] = int(255.99 * col.g());
      buffer[image_pixel(x, y) + 2] = int(255.99 * col.b());
    }
    std::cout << "\r" << std::setw(2) << std::setfill(' ') 
              << y * 100 / HEIGHT << '%' << std::flush;
  }

  std::cout << "\r" << " - Done!" << std::flush << std::endl << std::endl;
  
  std::cout << "Saving image..." << std::endl;
  stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, buffer.get(), 0);
  std::cout << " - Done!" << std::endl;
  return 0;
}
