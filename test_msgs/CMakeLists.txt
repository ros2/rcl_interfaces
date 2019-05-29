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

rosidl_generate_interfaces(${PROJECT_NAME}
  ${test_interface_files_MSG_FILES}
  ${test_interface_files_SRV_FILES}
  ${test_interface_files_ACTION_FILES}
  "msg/Builtins.msg"
  "action/NestedMessage.action"
  DEPENDENCIES builtin_interfaces
  ADD_LINTER_TESTS
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  ament_add_gtest(test_action_typesupport_c_builds
    test/test_c_type_support.cpp)
  target_include_directories(test_action_typesupport_c_builds PRIVATE
    include)
  target_link_libraries(test_action_typesupport_c_builds
    ${_AMENT_EXPORT_LIBRARIES})

  ament_add_gtest(test_action_typesupport_cpp_builds
    test/test_cpp_type_support.cpp)
  target_include_directories(test_action_typesupport_cpp_builds PRIVATE
    include)
  target_link_libraries(test_action_typesupport_cpp_builds
    ${_AMENT_EXPORT_LIBRARIES})
endif()

if(DEFINED PYTHON_INSTALL_DIR)
  install(DIRECTORY src/test_msgs
    DESTINATION "${PYTHON_INSTALL_DIR}")
endif()

install(DIRECTORY include/
  DESTINATION include)

ament_export_dependencies(rosidl_default_runtime)
ament_export_include_directories(include)
ament_package()
