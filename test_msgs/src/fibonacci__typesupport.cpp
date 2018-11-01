// generated from rosidl_typesupport_cpp/resource/srv__type_support.cpp.em
// generated code does not contain a copyright notice

#include <action_msgs/msg/goal_status_array.hpp>
#include <action_msgs/srv/cancel_goal.hpp>
#include "rosidl_generator_c/action_type_support_struct.h"
#include "rosidl_generator_cpp/action_type_support_decl.hpp"
#include "rosidl_generator_cpp/message_type_support_decl.hpp"
#include "rosidl_generator_cpp/service_type_support_decl.hpp"
#include <test_msgs/action/fibonacci__feedback.hpp>
#include <test_msgs/action/fibonacci__goal.hpp>
#include <test_msgs/action/fibonacci__result.hpp>
#include <test_msgs/action/fibonacci__struct.hpp>
#include "test_msgs/msg/rosidl_generator_c__visibility_control.h"

namespace test_msgs
{
namespace action
{
namespace rosidl_generator_cpp
{
static rosidl_action_type_support_t Fibonacci_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL};
}
}
}

namespace rosidl_generator_cpp
{

template<>
ROSIDL_GENERATOR_C_PUBLIC_test_msgs
const rosidl_action_type_support_t *
get_action_type_support_handle<::test_msgs::action::Fibonacci>()
{
  using ::test_msgs::action::rosidl_generator_cpp::Fibonacci_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  Fibonacci_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::test_msgs::action::Fibonacci::GoalRequestService>();
  Fibonacci_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::test_msgs::action::Fibonacci::GoalResultService>();
  Fibonacci_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::test_msgs::action::Fibonacci::CancelGoalService>();
  Fibonacci_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::test_msgs::action::Fibonacci::Feedback>();
  Fibonacci_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::test_msgs::action::Fibonacci::GoalStatusMessage>();
  return &Fibonacci_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp
