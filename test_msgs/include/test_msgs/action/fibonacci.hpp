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

#ifndef TEST_MSGS__ACTION__FIBONACCI_HPP_
#define TEST_MSGS__ACTION__FIBONACCI_HPP_

#include <action_msgs/msg/goal_info.hpp>
#include <action_msgs/msg/goal_status_array.hpp>
#include <action_msgs/srv/cancel_goal.hpp>
#include "rosidl_generator_c/message_type_support_struct.h"
#include "rosidl_generator_c/service_type_support_struct.h"
#include <test_msgs/action/fibonacci__goal.hpp>
#include <test_msgs/action/fibonacci__result.hpp>
#include <test_msgs/action/fibonacci__feedback.hpp>

// TODO(sloretz) define these in rosidl_typesupport_cpp
namespace rosidl_typesupport_cpp
{
  template <typename ACTION>
  const rosidl_service_type_support_t *
  get_action_goal_request_typesupport_handle_function(
    const rosidl_service_type_support_t * handle, const char * identifier)
  {
    return get_service_typesupport_handle_function<ACTION::GoalRequestService>(
        handle, identifier);
  }

  template <typename ACTION>
  const rosidl_service_type_support_t *
  get_action_goal_result_typesupport_handle_function(
    const rosidl_service_type_support_t * handle, const char * identifier)
  {
    return get_service_typesupport_handle_function<ACTION::GoalResponseService>(
        handle, identifier);
  }

  template <typename ACTION>
  const rosidl_service_type_support_t *
  get_action_cancel_goal_typesupport_handle_function(
    const rosidl_service_type_support_t * handle, const char * identifier)
  {
    return get_service_typesupport_handle_function<ACTION::CancelGoalService>(
        handle, identifier);
  }

  template <typename ACTION>
  const rosidl_message_type_support_t *
  get_action_feedback_typesupport_handle_function(
    const rosidl_message_type_support_t * handle, const char * identifier)
  {
    return get_message_typesupport_handle_function<ACTION::Feedback>(
        handle, identifier);
  }

  template <typename ACTION>
  const rosidl_message_type_support_t *
  get_action_status_typesupport_handle_function(
    const rosidl_message_type_support_t * handle, const char * identifier)
  {
    return get_message_typesupport_handle_function<ACTION::GoalStatusMessage>(
        handle, identifier);
  }
}
// TODO(sloretz) end todo

namespace test_msgs
{
namespace action
{
struct Fibonacci
{
  // Typedefs handy for rcl and rclcpp
  using CancelGoalService = action_msgs::srv::CancelGoal;
  using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  using GoalRequestService = test_msgs::action::Fibonacci_Goal;
  using GoalResultService = test_msgs::action::Fibonacci_Result;

  // Typedefs handy for user
  using Goal = GoalRequestService::Request;
  using Result = GoalResultService::Response;
  using Feedback = test_msgs::action::Fibonacci_Feedback;
};
}
}

#endif  // TEST_MSGS__ACTION__FIBONACCI_HPP_
