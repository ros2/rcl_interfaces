// Copyright 2018 Open Source Robotics Foundation, Inc.
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

// TODO(sloretz) generated code should not contain a copyright notice

#include <action_msgs/msg/goal_status_array.hpp>
#include <action_msgs/srv/cancel_goal.hpp>
#include <test_msgs/action/fibonacci__feedback.hpp>
#include <test_msgs/action/fibonacci__goal.hpp>
#include <test_msgs/action/fibonacci__result.hpp>
#include <test_msgs/action/fibonacci__struct.hpp>
#include "rosidl_generator_c/action_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
#include "rosidl_typesupport_cpp/action_type_support.hpp"
#include "test_msgs/action/rosidl_generator_c__visibility_control.h"

namespace test_msgs
{
namespace action
{
namespace rosidl_generator_cpp
{
static rosidl_action_type_support_t Fibonacci_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL};
}  // namespace rosidl_generator_cpp
}  // namespace action
}  // namespace test_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_GENERATOR_C_PUBLIC_test_msgs_ACTION
const rosidl_action_type_support_t *
get_action_type_support_handle<::test_msgs::action::Fibonacci>()
{
  using ::test_msgs::action::rosidl_generator_cpp::Fibonacci_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  Fibonacci_action_type_support_handle.goal_service_type_support =
    get_service_type_support_handle<::test_msgs::action::Fibonacci::GoalRequestService>();
  Fibonacci_action_type_support_handle.result_service_type_support =
    get_service_type_support_handle<::test_msgs::action::Fibonacci::GoalResultService>();
  Fibonacci_action_type_support_handle.cancel_service_type_support =
    get_service_type_support_handle<::test_msgs::action::Fibonacci::CancelGoalService>();
  Fibonacci_action_type_support_handle.feedback_message_type_support =
    get_message_type_support_handle<::test_msgs::action::Fibonacci::Feedback>();
  Fibonacci_action_type_support_handle.status_message_type_support =
    get_message_type_support_handle<::test_msgs::action::Fibonacci::GoalStatusMessage>();
  return &Fibonacci_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp
