// Copyright 2023 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cassert>
#include <gtest/gtest.h>

#include <type_description_interfaces_utils/utils.h>

#include <rcutils/logging_macros.h>
#include <rcutils/qsort.h>
#include <rcutils/types/rcutils_ret.h>
#include <rcutils/types/hash_map.h>
#include <rosidl_runtime_c/string_functions.h>

#include <type_description_interfaces/msg/field.h>
#include <type_description_interfaces/msg/individual_type_description.h>
#include <type_description_interfaces/msg/type_description.h>


TEST(Utils, test_construction)
{
  type_description_interfaces__msg__TypeDescription * desc =
    type_description_interfaces__msg__TypeDescription__create();

  type_description_interfaces__msg__Field * field = NULL;
  type_description_interfaces_utils_create_field(
    "ROS 2", strlen("ROS 2"), 2,  // Name, Name Length, Type ID
    0, 0,       // Capacity, String Capacity
    "", 0,      // Nested Type Name, Nested Type Name Length
    "", 0,      // Default Value, Default Value Length
    &field);

  type_description_interfaces_utils_append_field(
    &desc->type_description, field);

  type_description_interfaces_utils_print_type_description(desc);

  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  rcutils_hash_map_t * hash_map = NULL;
  type_description_interfaces_utils_get_field_map(
    &desc->type_description, &allocator, &hash_map);

  type_description_interfaces_utils_print_field_map(hash_map);

  // TODO(methylDragon): Check to see if finalizing the map causes obtained keys
  // to segfault
}
