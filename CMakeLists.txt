cmake_minimum_required(VERSION 3.13)
project(bitmap)
include_directories(include)
add_library(bitmap SHARED src/bitmap.c)
