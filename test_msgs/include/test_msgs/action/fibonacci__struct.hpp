// No copywrite in generated code
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
}
}

#endif  // TEST_MSGS__ACTION__FIBONACCI__STRUCT_HPP_

