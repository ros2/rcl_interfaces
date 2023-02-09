cmake_minimum_required(VERSION 3.5)

project(action_msgs)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
# Depend on "core" generators instead of "default" generators
# because ROS actions depend on this package
find_package(rosidl_core_generators REQUIRED)
find_package(unique_identifier_msgs REQUIRED)

set(msg_files
  "msg/GoalInfo.msg"
  "msg/GoalStatus.msg"
  "msg/GoalStatusArray.msg"
)
set(srv_files
  "srv/CancelGoal.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  DEPENDENCIES builtin_interfaces unique_identifier_msgs
  ADD_LINTER_TESTS
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_core_runtime)

ament_package()
