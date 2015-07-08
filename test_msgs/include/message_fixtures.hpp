// Copyright 2015 Open Source Robotics Foundation, Inc.
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

#ifndef __test_communication__message_fixtures__hpp__
#define __test_communication__message_fixtures__hpp__

#include <vector>

#include <test_communication/msg/builtins.hpp>
#include <test_communication/msg/dynamic_array_nested.hpp>
#include <test_communication/msg/dynamic_array_primitives.hpp>
#include <test_communication/msg/empty.hpp>
#include <test_communication/msg/nested.hpp>
#include <test_communication/msg/primitives.hpp>
#include <test_communication/msg/static_array_primitives.hpp>


std::vector<test_communication::msg::Empty::SharedPtr>
get_messages_empty()
{
  std::vector<test_communication::msg::Empty::SharedPtr> messages;
  auto msg = std::make_shared<test_communication::msg::Empty>();
  messages.push_back(msg);
  return messages;
}

std::vector<test_communication::msg::Primitives::SharedPtr>
get_messages_primitives()
{
  std::vector<test_communication::msg::Primitives::SharedPtr> messages;
  {
    auto msg = std::make_shared<test_communication::msg::Primitives>();
    msg->bool_value = false;
    msg->byte_value = 0;
    msg->char_value = '\0';
    msg->float32_value = 0.0f;
    msg->float64_value = 0;
    msg->int8_value = 0;
    msg->uint8_value = 0;
    msg->int16_value = 0;
    msg->uint16_value = 0;
    msg->int32_value = 0;
    msg->uint32_value = 0;
    msg->int64_value = 0;
    msg->uint64_value = 0;
    msg->string_value = "";
    messages.push_back(msg);
  }
  {
    auto msg = std::make_shared<test_communication::msg::Primitives>();
    msg->bool_value = true;
    msg->byte_value = 255;
    msg->char_value = 0xff;
    msg->float32_value = 1.11f;
    msg->float64_value = 1.11;
    msg->int8_value = 127;
    msg->uint8_value = 255;
    msg->int16_value = 32767;
    msg->uint16_value = 65535;
    msg->int32_value = 2147483647;
    msg->uint32_value = 4294967295;
    msg->int64_value = 9223372036854775807;
    msg->uint64_value = 18446744073709551615UL;
    msg->string_value = "max value";
    messages.push_back(msg);
  }
  {
    auto msg = std::make_shared<test_communication::msg::Primitives>();
    msg->bool_value = false;
    msg->byte_value = 0;
    msg->char_value = 0x0;
    msg->float32_value = -2.22f;
    msg->float64_value = -2.22;
    msg->int8_value = -128;
    msg->uint8_value = 0;
    msg->int16_value = -32768;
    msg->uint16_value = 0;
    msg->int32_value = -2147483648;
    msg->uint32_value = 0;
    msg->int64_value = -9223372036854775808UL;
    msg->uint64_value = 0;
    msg->string_value = "min value";
    messages.push_back(msg);
  }
  return messages;
}

std::vector<test_communication::msg::StaticArrayPrimitives::SharedPtr>
get_messages_static_array_primitives()
{
  std::vector<test_communication::msg::StaticArrayPrimitives::SharedPtr> messages;
  {
    auto msg = std::make_shared<test_communication::msg::StaticArrayPrimitives>();
    msg->bool_values = {{false, true, false}};
    msg->byte_values = {{0, 0xff, 0}};
    msg->char_values = {{'\0', '\255', '\0'}};
    msg->float32_values = {{0.0f, 1.11f, -2.22f}};
    msg->float64_values = {{0, 1.11, -2.22}};
    msg->int8_values = {{0, 127, -128}};
    msg->uint8_values = {{0, 255, 0}};
    msg->int16_values = {{0, 32767, -32768}};
    msg->uint16_values = {{0, 65535, 0}};
    msg->int32_values = {{
      static_cast<int32_t>(0),
      static_cast<int32_t>(2147483647),
      static_cast<int32_t>(-2147483648)
    }};
    msg->uint32_values = {{0, 4294967295, 0}};
    msg->int64_values[0] = 0;
    msg->int64_values[1] = 9223372036854775807;
    msg->int64_values[2] = -9223372036854775808UL;
    msg->uint64_values = {{0, 18446744073709551615UL, 0}};
    msg->string_values = {{"", "max value", "min value"}};
    messages.push_back(msg);
  }
  return messages;
}

std::vector<test_communication::msg::DynamicArrayPrimitives::SharedPtr>
get_messages_dynamic_array_primitives()
{
  std::vector<test_communication::msg::DynamicArrayPrimitives::SharedPtr> messages;
  {
    auto msg = std::make_shared<test_communication::msg::DynamicArrayPrimitives>();
    msg->bool_values = {{}};
    msg->byte_values = {{}};
    msg->char_values = {{}};
    msg->float32_values = {{}};
    msg->float64_values = {{}};
    msg->int8_values = {{}};
    msg->uint8_values = {{}};
    msg->int16_values = {{}};
    msg->uint16_values = {{}};
    msg->int32_values = {{}};
    msg->uint32_values = {{}};
    msg->int64_values = {{}};
    msg->uint64_values = {{}};
    msg->string_values = {{}};
    messages.push_back(msg);
  }
  {
    auto msg = std::make_shared<test_communication::msg::DynamicArrayPrimitives>();
    msg->bool_values = {true};
    msg->byte_values = {0xff};
    msg->char_values = {'\255'};
    msg->float32_values = {1.11f};
    msg->float64_values = {1.11};
    msg->int8_values = {127};
    msg->uint8_values = {255};
    msg->int16_values = {32767};
    msg->uint16_values = {65535};
    msg->int32_values = {2147483647};
    msg->uint32_values = {4294967295};
    msg->int64_values = {9223372036854775807};
    msg->uint64_values = {18446744073709551615UL};
    msg->string_values = {{"max value"}};
    messages.push_back(msg);
  }
  {
    auto msg = std::make_shared<test_communication::msg::DynamicArrayPrimitives>();
    msg->bool_values = {{false, true}};
    msg->byte_values = {{0, 0xff}};
    msg->char_values = {{'\0', '\255'}};
    msg->float32_values = {{0.0f, 1.11f, -2.22f}};
    msg->float64_values = {{0, 1.11, -2.22}};
    msg->int8_values = {{0, 127, -128}};
    msg->uint8_values = {{0, 255}};
    msg->int16_values = {{0, 32767, -32768}};
    msg->uint16_values = {{0, 65535}};
    // The narrowing static cast is required to avoid build errors on Windows.
    msg->int32_values = {{
      static_cast<int32_t>(0),
      static_cast<int32_t>(2147483647),
      static_cast<int32_t>(-2147483648)
    }};
    msg->uint32_values = {{0, 4294967295}};
    msg->int64_values.resize(3);
    msg->int64_values[0] = 0;
    msg->int64_values[1] = 9223372036854775807;
    msg->int64_values[2] = -9223372036854775808UL;
    msg->uint64_values = {{0, 18446744073709551615UL}};
    msg->string_values = {{"", "max value", "optional min value"}};
    messages.push_back(msg);
  }
  return messages;
}

std::vector<test_communication::msg::Nested::SharedPtr>
get_messages_nested()
{
  std::vector<test_communication::msg::Nested::SharedPtr> messages;
  auto primitive_msgs = get_messages_primitives();
  for (auto primitive_msg : primitive_msgs) {
    auto msg = std::make_shared<test_communication::msg::Nested>();
    msg->primitive_values = *primitive_msg;
    messages.push_back(msg);
  }
  return messages;
}

std::vector<test_communication::msg::DynamicArrayNested::SharedPtr>
get_messages_dynamic_array_nested()
{
  std::vector<test_communication::msg::DynamicArrayNested::SharedPtr> messages;
  {
    auto msg = std::make_shared<test_communication::msg::DynamicArrayNested>();
    auto primitive_msgs = get_messages_primitives();
    for (auto primitive_msg : primitive_msgs) {
      msg->primitive_values.push_back(*primitive_msg);
    }
    messages.push_back(msg);
  }
  return messages;
}

std::vector<test_communication::msg::Builtins::SharedPtr>
get_messages_builtins()
{
  std::vector<test_communication::msg::Builtins::SharedPtr> messages;
  {
    auto msg = std::make_shared<test_communication::msg::Builtins>();
    msg->duration_value.sec = -1234567890;
    msg->duration_value.nanosec = 123456789;
    msg->time_value.sec = -1234567890;
    msg->time_value.nanosec = 987654321;
    messages.push_back(msg);
  }
  return messages;
}

#endif  // __test_communication__message_fixtures__hpp__
