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

#include <test_communication/DynamicArrayPrimitives.h>
#include <test_communication/Empty.h>
#include <test_communication/Primitives.h>
#include <test_communication/StaticArrayPrimitives.h>


std::vector<test_communication::Empty::Ptr>
get_messages_empty()
{
  std::vector<test_communication::Empty::Ptr> messages;
  auto msg = std::make_shared<test_communication::Empty>();
  messages.push_back(msg);
  return messages;
}

std::vector<test_communication::Primitives::Ptr>
get_messages_primitives()
{
  std::vector<test_communication::Primitives::Ptr> messages;
  {
    auto msg = std::make_shared<test_communication::Primitives>();
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
    auto msg = std::make_shared<test_communication::Primitives>();
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
    auto msg = std::make_shared<test_communication::Primitives>();
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

std::vector<test_communication::StaticArrayPrimitives::Ptr>
get_messages_static_array_primitives()
{
  std::vector<test_communication::StaticArrayPrimitives::Ptr> messages;
  {
    auto msg = std::make_shared<test_communication::StaticArrayPrimitives>();
    msg->bool_values = {false, true, false};
    msg->byte_values = {0, 0xff, 0};
    msg->char_values = {'\0', '\255', '\0'};
    msg->float32_values = {0.0f, 1.11f, -2.22f};
    msg->float64_values = {0, 1.11, -2.22};
    msg->int8_values = {0, 127, -128};
    msg->uint8_values = {0, 255, 0};
    msg->int16_values = {0, 32767, -32768};
    msg->uint16_values = {0, 65535, 0};
    msg->int32_values = {0, 2147483647, -2147483648};
    msg->uint32_values = {0, 4294967295, 0};
    msg->int64_values[0] = 0;
    msg->int64_values[1] = 9223372036854775807;
    msg->int64_values[2] = -9223372036854775808UL;
    msg->uint64_values = {0, 18446744073709551615UL, 0};
    msg->string_values = {"", "max value", "min value"};
    messages.push_back(msg);
  }
  return messages;
}

std::vector<test_communication::DynamicArrayPrimitives::Ptr>
get_messages_dynamic_array_primitives()
{
  std::vector<test_communication::DynamicArrayPrimitives::Ptr> messages;
  {
    auto msg = std::make_shared<test_communication::DynamicArrayPrimitives>();
    msg->bool_values = {};
    msg->byte_values = {};
    msg->char_values = {};
    msg->float32_values = {};
    msg->float64_values = {};
    msg->int8_values = {};
    msg->uint8_values = {};
    msg->int16_values = {};
    msg->uint16_values = {};
    msg->int32_values = {};
    msg->uint32_values = {};
    msg->int64_values = {};
    msg->uint64_values = {};
    msg->string_values = {};
    messages.push_back(msg);
  }
  {
    auto msg = std::make_shared<test_communication::DynamicArrayPrimitives>();
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
    msg->string_values = {"max value"};
    messages.push_back(msg);
  }
  {
    auto msg = std::make_shared<test_communication::DynamicArrayPrimitives>();
    msg->bool_values = {false, true};
    msg->byte_values = {0, 0xff};
    msg->char_values = {'\0', '\255'};
    msg->float32_values = {0.0f, 1.11f, -2.22f};
    msg->float64_values = {0, 1.11, -2.22};
    msg->int8_values = {0, 127, -128};
    msg->uint8_values = {0, 255};
    msg->int16_values = {0, 32767, -32768};
    msg->uint16_values = {0, 65535};
    msg->int32_values = {0, 2147483647, -2147483648};
    msg->uint32_values = {0, 4294967295};
    msg->int64_values.resize(3);
    msg->int64_values[0] = 0;
    msg->int64_values[1] = 9223372036854775807;
    msg->int64_values[2] = -9223372036854775808UL;
    msg->uint64_values = {0, 18446744073709551615UL};
    msg->string_values = {"", "max value", "optional min value"};
    messages.push_back(msg);
  }
  return messages;
}

#endif  // __test_communication__message_fixtures__hpp__
