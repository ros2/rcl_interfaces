cmake_minimum_required(VERSION 2.8.3)

project(rcl_interfaces)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ament_export_dependencies(rcl_interfaces)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Parameter.msg"
  "msg/ParameterDescription.msg"
  "msg/ParameterEvent.msg"
  "srv/DescribeParameters.srv"
  "srv/GetParameters.srv"
  "srv/HasParameters.srv"
  "srv/ListParameters.srv"
  "srv/SetParameters.srv"
)

# this must happen before the invocation of ament_package()
if(AMENT_ENABLE_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
