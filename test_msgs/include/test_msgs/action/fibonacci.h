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

#ifndef TEST_MSGS__ACTION__FIBONACCI_H_
#define TEST_MSGS__ACTION__FIBONACCI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "rosidl_typesupport_interface/macros.h"
#include <action_msgs/msg/goal_info.h>
#include <action_msgs/msg/goal_status_array.h>
#include <action_msgs/msg/cancel_goal.h>
#include <test_msgs/action/fibonacci_goal_request.h>
#include <test_msgs/action/fibonacci_goal_result.h>
#include <test_msgs/action/fibonacci_feedback.h>


// TODO(sloretz) define these macros in rosidl_typesupport_interface,
// or rosidl_generator_c, or rosidl_type_support_c

#define ROSIDL_GET_ACTION_GOAL_REQUEST(package, action) \
  ROSIDL_TYPESUPPORT_INTERFACE__ ##  package ## __ACTION__ ## action ## __GOAL_REQUEST_SYMBOL_NAME

#define ROSIDL_GET_ACTION_GOAL_RESPONSE(package, action) \
  ROSIDL_TYPESUPPORT_INTERFACE__ ##  package ## __ACTION__ ## action ## __GOAL_RESPONSE_SYMBOL_NAME

#define ROSIDL_GET_ACTION_FEEDBACK(package, action) \
  ROSIDL_TYPESUPPORT_INTERFACE__ ##  package ## __ACTION__ ## action ## __FEEDBACK_SYMBOL_NAME

#define ROSIDL_GET_ACTION_STATUS(package, action) \
  ROSIDL_TYPESUPPORT_INTERFACE__ ##  package ## __ACTION__ ## action ## __STATUS_SYMBOL_NAME

#define ROSIDL_GET_ACTION_CANCEL_REQUEST(package, action) \
  ROSIDL_TYPESUPPORT_INTERFACE__ ##  package ## __ACTION__ ## action ## __CANCEL_REQUEST_SYMBOL_NAME

// TODO(sloretz) end todo


#define ROSIDL_TYPESUPPORT_INTERFACE__TEST_MSGS__ACTION__FIBONACCI__GOAL_REQUEST_SYMBOL_NAME \
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, FibonacciGoalRequest)

#define ROSIDL_TYPESUPPORT_INTERFACE__TEST_MSGS__ACTION__FIBONACCI__GOAL_RESPONSE_SYMBOL_NAME \
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, FibonacciGoalResponse)

#define ROSIDL_TYPESUPPORT_INTERFACE__TEST_MSGS__ACTION__FIBONACCI__FEEDBACK_SYMBOL_NAME \
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, test_msgs, action, FibonacciFeedback)

// TODO(sloretz) not sure these are needed since it's always the same symbol
#define ROSIDL_TYPESUPPORT_INTERFACE__TEST_MSGS__ACTION__FIBONACCI__STATUS_SYMBOL_NAME \
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)

#define ROSIDL_TYPESUPPORT_INTERFACE__TEST_MSGS__ACTION__FIBONACCI__CANCEL_REQUEST_SYMBOL_NAME \
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, action_msgs, srv, CancelGoal)

#ifdef __cplusplus
}
#endif

#define TEST_MSGS__ACTION__FIBONACCI_H_
