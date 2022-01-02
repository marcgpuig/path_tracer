load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
  name = "stb_cc",
  deps = [
    ":stb_image_resize_cc",
    ":stb_image_write_cc",
    ":stb_image_cc",
    ":stb_perlin_cc",
  ],
  visibility = ["//src:__pkg__"],
)

cc_library(
  name = "stb_image_resize_cc",
  hdrs = [
    "stb_image_resize.h",
  ],
  visibility = ["//src:__pkg__"],
)

cc_library(
  name = "stb_image_write_cc",
  hdrs = [
    "stb_image_write.h",
  ],
  visibility = ["//src:__pkg__"],
)

cc_library(
  name = "stb_image_cc",
  hdrs = [
    "stb_image.h",
  ],
  visibility = ["//src:__pkg__"],
)

cc_library(
  name = "stb_perlin_cc",
  hdrs = [
    "stb_perlin.h",
  ],
  visibility = ["//src:__pkg__"],
)
