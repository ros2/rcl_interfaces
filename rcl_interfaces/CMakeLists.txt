cmake_minimum_required(VERSION 2.8.3)

project(rcl_interfaces)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

find_package(ament_cmake REQUIRED)
find_package(builtin_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ament_export_dependencies(rcl_interfaces)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Param.msg"
  "msg/ParamDescription.msg"
  "srv/GetParams.srv"
  "srv/HasParam.srv"
  "srv/ListParamsByPrefix.srv"
  "srv/SetParams.srv"
  DEPENDENCIES builtin_msgs
)

ament_package()
