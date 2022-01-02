load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
  name = "main",
  copts = ["-std=c++17"],
  srcs = [
    "main.cpp",
    "camera.h",
    "hitable_list.h",
    "hitable.h",
    "material.h",
    "random_engine.h",
    "ray.h",
    "sphere.h",
    "vec3.h",
  ],
  deps = [
    "//lib/stb:stb_cc",
  ],
)