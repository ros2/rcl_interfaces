cmake_minimum_required(VERSION 3.5)

project(lifecycle_msgs)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/State.msg"
  "msg/Transition.msg"
  "msg/TransitionDescription.msg"
  "msg/TransitionEvent.msg"
)
set(srv_files
  "srv/ChangeState.srv"
  "srv/GetAvailableStates.srv"
  "srv/GetAvailableTransitions.srv"
  "srv/GetState.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  ADD_LINTER_TESTS
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)

ament_package()
