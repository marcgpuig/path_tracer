#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "random_engine.h"
#include "material.h"

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
const uint16_t SAMPLES = 20;
const uint16_t BOUNCES = 10;

int64_t image_pixel(const int32_t &x, const int32_t &y)
{
  return ((HEIGHT - 1 - y) * WIDTH + x) * CHANNELS;
}

vec3 color(const ray &r, hitable *world, int depth)
{
  hit_record rec;
  // the 0.001 solves the "acne problem" in shadows
  if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec))
  {
    ray scattered;
    vec3 attenuation;
    if (depth > 0 && rec.mat->scatter(r, rec, attenuation, scattered))
    {
      return attenuation * color(scattered, world, depth - 1);
    }
    else return vec3::zeros();
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
  list[0] = new sphere(vec3( 0,-100.5,-1), 100, new lambertian(vec3(0.48, 0.55, 0.19)));
  list[1] = new sphere(vec3(-1.0,0,-1), 0.5, new dielectric(1.5));
  list[2] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.95, 0.56, 0.22)));
  list[3] = new sphere(vec3(1.0,0,-1), 0.5, new metal(vec3(0.10, 0.51, 0.56), .2));
  hitable *world = new hitable_list(list, object_num);
  vec3 cam_pos(13,2,3);
  vec3 cam_look(0,0,0);
  double dist_to_focus = (cam_pos - cam_look).length();
  double aperture = 0.2;
  camera cam(cam_pos, cam_look, vec3(0,1,0), 20, float(WIDTH) / float(HEIGHT), aperture, dist_to_focus);

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
        col += color(r, world, BOUNCES);
      }
      col /= float(SAMPLES);
      col /= vec3(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));

      buffer[image_pixel(x, y) + 0] = int(255.99 * col.r());
      buffer[image_pixel(x, y) + 1] = int(255.99 * col.g());
      buffer[image_pixel(x, y) + 2] = int(255.99 * col.b());
    }
    size_t percent = y * 100 / HEIGHT;
    std::cout << "\r" << "[";
    for (size_t i = 0; i < percent/2; i++) std::cout << "#";
    for (size_t i = 0; i < 50 - (percent/2); i++) std::cout << "-";
    std::cout << "]  " << std::setw(2) << std::setfill(' ') << percent << "%";
    std::cout << std::flush;
  }

  std::cout << "\r" << "                                                          " << std::flush;
  std::cout << "\r" << " - Done!" << std::endl << std::endl;
  std::cout << "Saving image..." << std::endl;

  stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, buffer.get(), 0);
  std::cout << " - Done!" << std::endl;

  return 0;
}
