cmake_minimum_required(VERSION 3.5)

project(rcl_interfaces)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# ament_export_dependencies(rcl_interfaces)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/IntraProcessMessage.msg"
  "msg/ListParametersResult.msg"
  "msg/ParameterDescriptor.msg"
  "msg/ParameterEventDescriptors.msg"
  "msg/ParameterEvent.msg"
  "msg/Parameter.msg"
  "msg/ParameterType.msg"
  "msg/ParameterValue.msg"
  "msg/SetParametersResult.msg"
  "srv/DescribeParameters.srv"
  "srv/GetParameters.srv"
  "srv/GetParameterTypes.srv"
  "srv/ListParameters.srv"
  "srv/SetParametersAtomically.srv"
  "srv/SetParameters.srv"
)

# this must happen before the invocation of ament_package()
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
