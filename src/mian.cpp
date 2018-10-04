#include <iostream>
#include <cstdint>
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

const int32_t WIDTH = 300;
const int32_t HEIGHT = 200;
const uint8_t CHANNELS = 3;
const int64_t TOTAL_BYTES = WIDTH * HEIGHT * CHANNELS;

int64_t image_pixel(const int32_t &x, const int32_t &y)
{
  return ((HEIGHT - 1 - y) * WIDTH + x) * CHANNELS;
}

int main(int argc, char const *argv[])
{
  uint8_t buffer[TOTAL_BYTES];

  for (int y = 0; y < HEIGHT; ++y)
  {
    for (int x = 0; x < WIDTH; ++x)
    {
      float r = float(x) / float(WIDTH);
      float g = float(y) / float(HEIGHT);
      float b = 0.0f;

      buffer[image_pixel(x, y) + 0] = int(255.99 * r);
      buffer[image_pixel(x, y) + 1] = int(255.99 * g);
      buffer[image_pixel(x, y) + 2] = int(255.99 * b);
    }
  }

  std::cout << "Saving image..." << std::endl;
  stbi_write_png("out.png", WIDTH, HEIGHT, CHANNELS, buffer, 0);

  vec3 a;
  std::cout << a << std::endl;

  vec3 b = {1,1,1};
  std::cout << b << std::endl;

  vec3 c{1,1,1};
  std::cout << c << std::endl;

  vec3 d(1,1,1);
  std::cout << d << std::endl;

  std::cout << b + b << std::endl;

  return 0;
}
