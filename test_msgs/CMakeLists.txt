cmake_minimum_required(VERSION 3.5)

project(test_msgs)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(msg_files
  "msg/BoundedArrayNested.msg"
  "msg/BoundedArrayPrimitives.msg"
  "msg/Builtins.msg"
  "msg/DynamicArrayNested.msg"
  "msg/DynamicArrayPrimitives.msg"
  "msg/DynamicArrayPrimitivesNested.msg"
  "msg/DynamicArrayStaticArrayPrimitivesNested.msg"
  "msg/Empty.msg"
  "msg/Nested.msg"
  "msg/Primitives.msg"
  "msg/StaticArrayNested.msg"
  "msg/StaticArrayPrimitives.msg"
)

set(srv_files
  "srv/Empty.srv"
  "srv/Primitives.srv"
)

# TODO(sloretz) actual action files instead of messages and services
set(action_files
  "action/DynamicArrayPrimitivesNested.msg"
  "action/Primitives.srv"
  "action/Something.msg"
  "action/SomethingElse.srv"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  ${action_files}
  DEPENDENCIES builtin_interfaces
  ADD_LINTER_TESTS
)

if(DEFINED PYTHON_INSTALL_DIR)
  install(DIRECTORY src/test_msgs
    DESTINATION "${PYTHON_INSTALL_DIR}/")
endif()

install(DIRECTORY include/
  DESTINATION include)

ament_export_dependencies(rosidl_default_runtime)
ament_export_include_directories(include)
ament_package()
