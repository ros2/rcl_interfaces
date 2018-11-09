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

#ifndef TEST_MSGS__ACTION__FIBONACCI__STRUCT_HPP_
#define TEST_MSGS__ACTION__FIBONACCI__STRUCT_HPP_

#include <action_msgs/msg/goal_info.hpp>
#include <action_msgs/msg/goal_status_array.hpp>
#include <action_msgs/srv/cancel_goal.hpp>
#include <test_msgs/action/fibonacci__goal.hpp>
#include <test_msgs/action/fibonacci__result.hpp>
#include <test_msgs/action/fibonacci__feedback.hpp>

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

typedef struct Fibonacci Fibonacci;
}  // namespace action
}  // namespace test_msgs

#endif  // TEST_MSGS__ACTION__FIBONACCI__STRUCT_HPP_
