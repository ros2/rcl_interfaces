cmake_minimum_required(VERSION 2.8.3)

project(rcl_interfaces)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)


ament_export_dependencies(rcl_interfaces)

ament_package()
