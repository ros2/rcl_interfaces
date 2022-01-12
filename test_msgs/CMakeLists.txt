cmake_minimum_required(VERSION 3.5)

project(test_msgs)

# Default to C11
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()

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
find_package(test_interface_files REQUIRED)

rosidl_generate_interfaces(test_msgs_interfaces
  ${test_interface_files_MSG_FILES}
  ${test_interface_files_SRV_FILES}
  ${test_interface_files_ACTION_FILES}
  ${test_interface_files_IDL_FILES}
  "msg/Builtins.msg"
  "action/NestedMessage.action"
  DEPENDENCIES builtin_interfaces
  ADD_LINTER_TESTS
)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>")

ament_export_targets(export_${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  rosidl_get_typesupport_target(c_typesupport_target "test_msgs_interfaces" "rosidl_typesupport_c")
  rosidl_get_typesupport_target(cpp_typesupport_target "test_msgs_interfaces" "rosidl_typesupport_cpp")

  ament_add_gtest(test_action_typesupport_c_builds
    test/test_c_type_support.cpp)
  target_link_libraries(test_action_typesupport_c_builds
    "${c_typesupport_target}")

  ament_add_gtest(test_action_typesupport_cpp_builds
    test/test_cpp_type_support.cpp)
  target_link_libraries(test_action_typesupport_cpp_builds
    "${cpp_typesupport_target}")
endif()

if(DEFINED PYTHON_INSTALL_DIR)
  install(DIRECTORY src/test_msgs
    DESTINATION "${PYTHON_INSTALL_DIR}")
endif()

install(DIRECTORY include/
  DESTINATION include)

install(TARGETS ${PROJECT_NAME} EXPORT export_${PROJECT_NAME})

ament_export_dependencies(rosidl_default_runtime)
ament_package()
