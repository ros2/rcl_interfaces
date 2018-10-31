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

#include <action_msgs/msg/goal_info.h>
#include <action_msgs/msg/goal_status_array.h>
#include <action_msgs/srv/cancel_goal.h>
#include <rosidl_generator_c/action_type_support_struct.h>
#include <test_msgs/action/fibonacci__goal.h>
#include <test_msgs/action/fibonacci__result.h>
#include <test_msgs/action/fibonacci__feedback.h>

#include "test_msgs/action/fibonacci__type_support.h"
#include "test_msgs/msg/rosidl_generator_c__visibility_control.h"


static rosidl_action_type_support_t _test_msgs__action__Fibonacci__typesupport_c;

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, Fibonacci)()
{
  // Thread-safe by always writing the same values to the static struct
  _test_msgs__action__Fibonacci__typesupport_c.goal_service_type_support = ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, Fibonacci_Goal)();
  _test_msgs__action__Fibonacci__typesupport_c.result_service_type_support = ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, Fibonacci_Result)();
  _test_msgs__action__Fibonacci__typesupport_c.cancel_service_type_support = ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _test_msgs__action__Fibonacci__typesupport_c.feedback_message_type_support = ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, Fibonacci_Feedback)();
  _test_msgs__action__Fibonacci__typesupport_c.status_message_type_support = ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_test_msgs__action__Fibonacci__typesupport_c;
}
