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
#include <vector>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb/stb_image_write.h"

const int32_t WIDTH = 450;
const int32_t HEIGHT = 200;
const uint8_t CHANNELS = 3;
const int64_t TOTAL_BYTES = WIDTH * HEIGHT * CHANNELS;
const uint16_t SAMPLES = 30;
const uint16_t BOUNCES = 6;

int64_t image_pixel(const int32_t &x, const int32_t &y)
{
  return ((HEIGHT - 1 - y) * WIDTH + x) * CHANNELS;
}

Vec3 color(const Ray &r, Hitable *world, int depth)
{
  HitRecord rec;
  // the 0.001 solves the "acne problem" in shadows
  if (world->hit(r, 0.001, std::numeric_limits<float>::max(), rec))
  {
    Ray scattered;
    Vec3 attenuation;
    if (depth > 0 && rec.mat->scatter(r, rec, attenuation, scattered))
    {
      return attenuation * color(scattered, world, depth - 1);
    }
    else return Vec3::zeros();
  }
  else
  {
    // Blends white and blue depending on the height of the y coord
    // unit vector -1.0 < uint_direction < 1.0
    Vec3 uint_direction = unit_vector(r.direction());
    // normalization 0.0 < t < 1.0
    double t = 0.5 * (uint_direction.y() + 1.0);
    // t = 1.0 = blue | t = 0.0 = white
    return (1.0 - t) * Vec3::ones() + t * Vec3(0.5, 0.7, 1.0);
  }
}

int main(int argc, char const *argv[])
{
  constexpr int total = 1;
  // constexpr double total_change = 1.0 / total;
  for (int im = 0; im < total; ++im)
  {
    // double change = total_change * im;
    auto buffer = std::make_unique<uint8_t[]>(TOTAL_BYTES);

    std::unique_ptr<HitableList> world = std::make_unique<HitableList>();
    world->add(
        std::make_unique<Sphere>(Vec3( 0, -500,0), 500.,
        std::make_unique<Lambertian>(Vec3(.7, .7, .7))));
    world->add(
        std::make_unique<Sphere>(Vec3(-3, .75,0), .75,
        std::make_unique<Dielectric>(1.5)));
    world->add(
        std::make_unique<Sphere>(Vec3(-1, .75,0), .75,
        std::make_unique<Lambertian>(Vec3(1, .3, 0.))));
    world->add(
        std::make_unique<Sphere>(Vec3( 1, .75,0), .75,
        std::make_unique<Metal>(Vec3(1., 1., 1.), 0.)));
    world->add(
        std::make_unique<Sphere>(Vec3( 3, .75,0), .75,
        std::make_unique<Metal>(Vec3(.39, .78, .85), 5.)));

    Vec3 cam_pos(0., 3., 10.);
    Vec3 cam_look(0, .75, 0.);
    const double dist_to_focus = (cam_pos - cam_look).length();
    const double aperture = 0.2;
    Camera cam(cam_pos, cam_look, Vec3(0., 1., 0.), 20, float(WIDTH) / float(HEIGHT), aperture, dist_to_focus);

    std::cout << "Rendering..." << std::endl;
    for (int y = 0; y < HEIGHT; ++y)
    {
      for (int x = 0; x < WIDTH; ++x)
      {
        Vec3 col;
        for (uint16_t i = 0; i < SAMPLES; ++i)
        {
          double u = double(x + dist(mt)) / double(WIDTH);
          double v = double(y + dist(mt)) / double(HEIGHT);
          Ray r = cam.get_ray(u, v);
          col += color(r, world.get(), BOUNCES);
        }
        col /= float(SAMPLES);
        col /= Vec3(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));

        buffer[image_pixel(x, y) + 0] = int(255.99 * col.r());
        buffer[image_pixel(x, y) + 1] = int(255.99 * col.g());
        buffer[image_pixel(x, y) + 2] = int(255.99 * col.b());
      }
      size_t percent = y * 100 / HEIGHT;
      std::cout << "\r" << "[";
      for (size_t i = 0; i < percent/2; i++) std::cout << "#";
      for (size_t i = 0; i < 50 - (percent/2); i++) std::cout << ".";
      std::cout << "]  " << std::setw(2) << std::setfill(' ') << percent << "%";
      std::cout << std::flush;
    }

    std::cout << "\r" << "                                                          " << std::flush;
    std::cout << "\r" << " - Done!" << std::endl;
    std::cout << "Saving image..." << std::endl;

    std::string im_name = "im_";
    im_name += std::to_string(im);
    im_name += ".png";

    stbi_write_png(im_name.c_str(), WIDTH, HEIGHT, CHANNELS, buffer.get(), 0);
    std::cout << " - Done!" << std::endl;
  }
  return 0;
}
