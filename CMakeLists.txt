cmake_minimum_required(VERSION 3.16)
project(dxwrap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(dxgi SHARED
  src/dxgi.cpp
  src/dxgi_adapter.hpp
  src/dxgi_device.hpp
  src/dxgi_factory.hpp
  src/dxgi_swap_chain.hpp
  src/logger.hpp
  src/logger.cpp)

add_library(d3d11 SHARED
  src/d3d11.cpp
  src/d3d11_device.hpp)
target_link_libraries(d3d11 PUBLIC dxgi)
