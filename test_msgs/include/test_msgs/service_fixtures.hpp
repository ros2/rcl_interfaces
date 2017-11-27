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

#ifndef TEST_MSGS__SERVICE_FIXTURES_HPP_
#define TEST_MSGS__SERVICE_FIXTURES_HPP_

#include <memory>
#include <utility>
#include <vector>

#include "test_msgs/message_fixtures.hpp"

#include "test_msgs/srv/bounded_array_nested.hpp"
#include "test_msgs/srv/bounded_array_primitives.hpp"
#include "test_msgs/srv/dynamic_array_nested.hpp"
#include "test_msgs/srv/dynamic_array_primitives.hpp"
#include "test_msgs/srv/dynamic_array_primitives_nested.hpp"
#include "test_msgs/srv/empty.hpp"
#include "test_msgs/srv/nested.hpp"
#include "test_msgs/srv/primitives.hpp"
#include "test_msgs/srv/static_array_nested.hpp"
#include "test_msgs/srv/static_array_primitives.hpp"


std::vector<
  std::pair<
    test_msgs::srv::Empty::Request::SharedPtr,
    test_msgs::srv::Empty::Response::SharedPtr
  >
>
get_services_empty()
{
  std::vector<
    std::pair<
      test_msgs::srv::Empty::Request::SharedPtr,
      test_msgs::srv::Empty::Response::SharedPtr
    >
  > services;
  auto request = std::make_shared<
    test_msgs::srv::Empty::Request>();
  auto reply = std::make_shared<
    test_msgs::srv::Empty::Response>();
  services.emplace_back(request, reply);
  return services;
}

std::vector<
  std::pair<
    test_msgs::srv::Primitives::Request::SharedPtr,
    test_msgs::srv::Primitives::Response::SharedPtr
  >
>
get_services_primitives()
{
  std::vector<
    std::pair<
      test_msgs::srv::Primitives::Request::SharedPtr,
      test_msgs::srv::Primitives::Response::SharedPtr
    >
  > services;
  {
    auto request = std::make_shared<test_msgs::srv::Primitives::Request>();
    request->bool_value = false;
    request->byte_value = 0;
    request->char_value = '\0';
    request->float32_value = 0.0f;
    request->float64_value = 0.0;
    request->int8_value = 0;
    request->uint8_value = 0;
    request->int16_value = 0;
    request->uint16_value = 0;
    request->int32_value = 0;
    request->uint32_value = 0;
    request->int64_value = 0;
    request->uint64_value = 0;
    request->string_value = "request";
    auto reply = std::make_shared<test_msgs::srv::Primitives::Response>();
    reply->bool_value = false;
    reply->byte_value = 0;
    reply->char_value = '\0';
    reply->float32_value = 0.0f;
    reply->float64_value = 0.0;
    reply->int8_value = 0;
    reply->uint8_value = 0;
    reply->int16_value = 0;
    reply->uint16_value = 0;
    reply->int32_value = 0;
    reply->uint32_value = 0;
    reply->int64_value = 0;
    reply->uint64_value = 0;
    reply->string_value = "reply";
    services.emplace_back(request, reply);
  }
  {
    auto request = std::make_shared<test_msgs::srv::Primitives::Request>();
    request->bool_value = true;
    request->byte_value = 1;
    request->char_value = 0x1;
    request->float32_value = 1.125f;
    request->float64_value = 1.125;
    request->int8_value = 1;
    request->uint8_value = 2;
    request->int16_value = 3;
    request->uint16_value = 4;
    request->int32_value = 5;
    request->uint32_value = 6;
    request->int64_value = 7;
    request->uint64_value = 8;
    // check strings longer then 256 characters
    request->string_value = "";
    for (size_t i = 0; i < 20000; ++i) {
      request->string_value += std::to_string(i % 10);
    }
    auto reply = std::make_shared<test_msgs::srv::Primitives::Response>();
    reply->bool_value = true;
    reply->byte_value = 11;
    reply->char_value = 0x11;
    reply->float32_value = 11.125f;
    reply->float64_value = 11.125;
    reply->int8_value = 11;
    reply->uint8_value = 22;
    reply->int16_value = 33;
    reply->uint16_value = 44;
    reply->int32_value = 55;
    reply->uint32_value = 66;
    reply->int64_value = 77;
    reply->uint64_value = 88;
    // check strings longer then 256 characters
    reply->string_value = "";
    for (size_t i = 0; i < 20000; ++i) {
      reply->string_value += std::to_string(i % 10);
    }
    services.emplace_back(request, reply);
  }
  return services;
}

std::vector<
  std::pair<
    test_msgs::srv::StaticArrayPrimitives::Request::SharedPtr,
    test_msgs::srv::StaticArrayPrimitives::Response::SharedPtr
  >
>
get_services_static_array_primitives()
{
  std::vector<
    std::pair<
      test_msgs::srv::StaticArrayPrimitives::Request::SharedPtr,
      test_msgs::srv::StaticArrayPrimitives::Response::SharedPtr
    >
  > service_pairs;
  {
    auto request = std::make_shared<test_msgs::srv::StaticArrayPrimitives::Request>();
    request->bool_values = {{false, true, false}};
    request->byte_values = {{0, 0xff, 0}};
    request->char_values = {{'\0', '\255', '\0'}};
    request->float32_values = {{0.0f, 11.125f, -22.125f}};
    request->float64_values = {{0, 11.125, -22.125}};
    // *INDENT-OFF* (prevent uncrustify from making unecessary indents here)
    request->int8_values = {{
      0, (std::numeric_limits<int8_t>::max)(), (std::numeric_limits<int8_t>::min)()}};
    request->uint8_values = {{0, (std::numeric_limits<uint8_t>::max)(), 0}};
    request->int16_values = {{
      0, (std::numeric_limits<int16_t>::max)(), (std::numeric_limits<int16_t>::min)()}};
    request->uint16_values = {{0, (std::numeric_limits<uint16_t>::max)(), 0}};
    request->int32_values = {{
      static_cast<int32_t>(0),
      (std::numeric_limits<int32_t>::max)(),
      (std::numeric_limits<int32_t>::min)()
    }};
    // *INDENT-ON*
    request->uint32_values = {{0, (std::numeric_limits<uint32_t>::max)(), 0}};
    request->int64_values[0] = 0;
    request->int64_values[1] = (std::numeric_limits<int64_t>::max)();
    request->int64_values[2] = (std::numeric_limits<int64_t>::min)();
    request->uint64_values = {{0, (std::numeric_limits<uint64_t>::max)(), 0}};
    request->string_values = {{"", "max value", "min value"}};

    auto response = std::make_shared<test_msgs::srv::StaticArrayPrimitives::Response>();
    response->bool_values = {{true, false, true}};
    response->byte_values = {{1, 0x0, 1}};
    response->char_values = {{'\x7f', '\0', '\x7f'}};
    response->float32_values = {{
      std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), 0.0f}};
    response->float64_values =  {{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max(), 0.0}};
    // *INDENT-OFF* (prevent uncrustify from making unecessary indents here)
    response->int8_values = {{
      0, (std::numeric_limits<int8_t>::max)(), (std::numeric_limits<int8_t>::min)()}};
    response->uint8_values = {{0, (std::numeric_limits<uint8_t>::max)(), 0}};
    response->int16_values = {{
      0, (std::numeric_limits<int16_t>::max)(), (std::numeric_limits<int16_t>::min)()}};
    response->uint16_values = {{0, (std::numeric_limits<uint16_t>::max)(), 0}};
    response->int32_values = {{
      static_cast<int32_t>(0),
      (std::numeric_limits<int32_t>::max)(),
      (std::numeric_limits<int32_t>::min)()
    }};
    // *INDENT-ON*
    response->uint32_values = {{(std::numeric_limits<uint32_t>::min)(), (std::numeric_limits<uint32_t>::max)(), 0}};
    response->int64_values[0] = 0;
    response->int64_values[1] = (std::numeric_limits<int64_t>::max)();
    response->int64_values[2] = (std::numeric_limits<int64_t>::min)();
    response->uint64_values = {{0, (std::numeric_limits<uint64_t>::max)(), 0}};
    response->string_values = {{"", "max value", "min value"}};

    service_pairs.emplace_back(request, response);
  }

  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::BoundedArrayPrimitives::Request::SharedPtr,
    test_msgs::srv::BoundedArrayPrimitives::Response::SharedPtr
  >
>
get_services_bounded_array_primitives()
{
  std::vector<
    std::pair<
      test_msgs::srv::BoundedArrayPrimitives::Request::SharedPtr,
      test_msgs::srv::BoundedArrayPrimitives::Response::SharedPtr
    >
  > service_pairs;
  {
    auto request = std::make_shared<test_msgs::srv::BoundedArrayPrimitives::Request>();
    request->bool_values = {};
    request->byte_values = {};
    request->char_values = {};
    request->float32_values = {};
    request->float64_values = {};
    request->int8_values = {};
    request->uint8_values = {};
    request->int16_values = {};
    request->uint16_values = {};
    request->int32_values = {};
    request->uint32_values = {};
    request->int64_values = {};
    request->uint64_values = {};
    request->string_values = {};
    request->check = 0;

    auto response = std::make_shared<test_msgs::srv::BoundedArrayPrimitives::Response>();
    response->bool_values = {true};
    response->byte_values = {0xff};
    response->char_values = {'\x7f'};
    response->float32_values = {1.125f};
    response->float64_values = {1.125};
    response->int8_values = {(std::numeric_limits<int8_t>::max)()};
    response->uint8_values = {(std::numeric_limits<uint8_t>::max)()};
    response->int16_values = {(std::numeric_limits<int16_t>::max)()};
    response->uint16_values = {(std::numeric_limits<uint16_t>::max)()};
    response->int32_values = {(std::numeric_limits<int32_t>::max)()};
    response->uint32_values = {(std::numeric_limits<uint32_t>::max)()};
    response->int64_values = {(std::numeric_limits<int64_t>::max)()};
    response->uint64_values = {(std::numeric_limits<uint64_t>::max)()};
    response->string_values = {{"max value"}};
    request->check = 1;

    service_pairs.emplace_back(request, response);
  }
  {
    auto request = std::make_shared<test_msgs::srv::BoundedArrayPrimitives::Request>();

    request->bool_values = {{false, true, false}};
    request->byte_values = {{0, 1, 0xff}};
    request->char_values = {{'\0', '\1', '\x7f'}};
    request->float32_values = {{0.0f, 1.125f, -2.125f}};
    request->float64_values = {{0, 1.125, -2.125}};
    request->int8_values = {{
      0, (std::numeric_limits<int8_t>::max)(), (std::numeric_limits<int8_t>::min)()}};
    request->uint8_values = {{0, 1, (std::numeric_limits<uint8_t>::max)()}};
    request->int16_values = {{
      0, (std::numeric_limits<int16_t>::max)(), (std::numeric_limits<int16_t>::min)()}};
    request->uint16_values = {{0, 1, (std::numeric_limits<uint16_t>::max)()}};
    // The narrowing static cast is required to avoid build errors on Windows.
    request->int32_values = {{
      static_cast<int32_t>(0),
      (std::numeric_limits<int32_t>::max)(),
      (std::numeric_limits<int32_t>::min)()
    }};
    request->uint32_values = {{0, 1, (std::numeric_limits<uint32_t>::max)()}};
    request->int64_values.resize(3);
    request->int64_values[0] = 0;
    request->int64_values[1] = (std::numeric_limits<int64_t>::max)();
    request->int64_values[2] = (std::numeric_limits<int64_t>::min)();
    request->uint64_values = {{0, 1, (std::numeric_limits<uint64_t>::max)()}};
    request->string_values = {{"", "max value", "optional min value"}};
    request->check = 2;

    auto response = std::make_shared<test_msgs::srv::BoundedArrayPrimitives::Response>();
    response->bool_values = {{true, false, true}};
    response->byte_values = {{0xff, 10, 11}};
    response->char_values = {{'\x7f', '\x0A', '\x0B'}};
    response->float32_values = {{-22.125f, 0.0f, 11.125f}};
    response->float64_values = {{-22.125, 0, 11.125}};
    response->int8_values = {{
      (std::numeric_limits<int8_t>::min)(), 0, (std::numeric_limits<int8_t>::max)()}};
    response->uint8_values = {{(std::numeric_limits<uint8_t>::max)(), 0, 1}};
    response->int16_values = {{
      (std::numeric_limits<int16_t>::min)(), 0, (std::numeric_limits<int16_t>::max)()}};
    response->uint16_values = {{(std::numeric_limits<uint16_t>::max)(), 0, 1}};
    // The narrowing static cast is required to avoid build errors on Windows.
    response->int32_values = {{
      (std::numeric_limits<int32_t>::min)(),
      static_cast<int32_t>(0),
      (std::numeric_limits<int32_t>::max)()
    }};
    response->uint32_values = {{(std::numeric_limits<uint32_t>::max)(), 0, 1}};
    response->int64_values.resize(3);
    response->int64_values[0] = (std::numeric_limits<int64_t>::min)();
    response->int64_values[1] = 0;
    response->int64_values[2] = (std::numeric_limits<int64_t>::max)();
    response->uint64_values = {{(std::numeric_limits<uint64_t>::max)(), 0, 1}};
    response->string_values = {{"optional min value", "", "max value"}};
    response->check = 2;
    service_pairs.emplace_back(request, response);
  }
  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::DynamicArrayPrimitives::Request::SharedPtr,
    test_msgs::srv::DynamicArrayPrimitives::Response::SharedPtr
  >
>
get_services_dynamic_array_primitives()
{
  std::vector<
    std::pair<
      test_msgs::srv::DynamicArrayPrimitives::Request::SharedPtr,
      test_msgs::srv::DynamicArrayPrimitives::Response::SharedPtr
    >
  > service_pairs;
  {
    auto request = std::make_shared<test_msgs::srv::DynamicArrayPrimitives::Request>();
    request->bool_values = {{}};
    request->byte_values = {{}};
    request->char_values = {{}};
    request->float32_values = {{}};
    request->float64_values = {{}};
    request->int8_values = {{}};
    request->uint8_values = {{}};
    request->int16_values = {{}};
    request->uint16_values = {{}};
    request->int32_values = {{}};
    request->uint32_values = {{}};
    request->int64_values = {{}};
    request->uint64_values = {{}};
    request->string_values = {{}};

    auto response = std::make_shared<test_msgs::srv::DynamicArrayPrimitives::Response>();
    response->bool_values = {true};
    response->byte_values = {0xff};
    response->char_values = {'\x7f'};
    response->float32_values = {1.125f};
    response->float64_values = {1.125};
    response->int8_values = {(std::numeric_limits<int8_t>::max)()};
    response->uint8_values = {(std::numeric_limits<uint8_t>::max)()};
    response->int16_values = {(std::numeric_limits<int16_t>::max)()};
    response->uint16_values = {(std::numeric_limits<uint16_t>::max)()};
    response->int32_values = {(std::numeric_limits<int32_t>::max)()};
    response->uint32_values = {(std::numeric_limits<uint32_t>::max)()};
    response->int64_values = {(std::numeric_limits<int64_t>::max)()};
    response->uint64_values = {(std::numeric_limits<uint64_t>::max)()};
    response->string_values = {{"max value"}};
    service_pairs.emplace_back(request, response);
  }
  {
    auto request = std::make_shared<test_msgs::srv::DynamicArrayPrimitives::Request>();
    request->bool_values = {{false, true}};
    request->byte_values = {{0, 0xff}};
    request->char_values = {{'\0', '\x7f'}};
    request->float32_values = {{0.0f, 1.125f, -2.125f}};
    request->float64_values = {{0, 1.125, -2.125}};
    // *INDENT-OFF* (prevent uncrustify from making unecessary indents here)
    request->int8_values = {{
      0, (std::numeric_limits<int8_t>::max)(), (std::numeric_limits<int8_t>::min)()}};
    request->uint8_values = {{0, (std::numeric_limits<uint8_t>::max)()}};
    request->int16_values = {{
      0, (std::numeric_limits<int16_t>::max)(), (std::numeric_limits<int16_t>::min)()}};
    request->uint16_values = {{0, (std::numeric_limits<uint16_t>::max)()}};
    // The narrowing static cast is required to avoid build errors on Windows.
    request->int32_values = {{
      static_cast<int32_t>(0),
      (std::numeric_limits<int32_t>::max)(),
      (std::numeric_limits<int32_t>::min)()
    }};
    // *INDENT-ON*
    request->uint32_values = {{0, (std::numeric_limits<uint32_t>::max)()}};
    request->int64_values.resize(3);
    request->int64_values[0] = 0;
    request->int64_values[1] = (std::numeric_limits<int64_t>::max)();
    request->int64_values[2] = (std::numeric_limits<int64_t>::min)();
    request->uint64_values = {{0, (std::numeric_limits<uint64_t>::max)()}};
    request->string_values = {{"", "max value", "optional min value"}};

    auto response = std::make_shared<test_msgs::srv::DynamicArrayPrimitives::Response>();
    // check sequences with more then 100 elements
    const size_t size = 1000;
    response->bool_values.resize(size);
    response->byte_values.resize(size);
    response->char_values.resize(size);
    response->float32_values.resize(size);
    response->float64_values.resize(size);
    response->int8_values.resize(size);
    response->uint8_values.resize(size);
    response->int16_values.resize(size);
    response->uint16_values.resize(size);
    response->int32_values.resize(size);
    response->uint32_values.resize(size);
    response->int64_values.resize(size);
    response->uint64_values.resize(size);
    response->string_values.resize(size);
    for (size_t i = 0; i < size; ++i) {
      response->bool_values[i] = (i % 2 != 0) ? true : false;
      response->byte_values[i] = static_cast<uint8_t>(i);
      response->char_values[i] = static_cast<char>(i % (1 << 7));
      response->float32_values[i] = 1.125f * i;
      response->float64_values[i] = 1.125 * i;
      response->int8_values[i] = static_cast<int8_t>(i);
      response->uint8_values[i] = static_cast<uint8_t>(i);
      response->int16_values[i] = static_cast<int16_t>(i);
      response->uint16_values[i] = static_cast<uint16_t>(i);
      response->int32_values[i] = static_cast<int32_t>(i);
      response->uint32_values[i] = static_cast<uint32_t>(i);
      response->int64_values[i] = i;
      response->uint64_values[i] = i;
      response->string_values[i] = std::to_string(i);
    }
    service_pairs.emplace_back(request, response);
  }
  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::Nested::Request::SharedPtr,
    test_msgs::srv::Nested::Response::SharedPtr
  >
>
get_services_nested()
{
  std::vector<
    std::pair<
      test_msgs::srv::Nested::Request::SharedPtr,
      test_msgs::srv::Nested::Response::SharedPtr
    >
  > service_pairs;
  auto primitive_msgs = get_messages_primitives();
  for (auto primitive_msg : primitive_msgs) {
    auto request = std::make_shared<test_msgs::srv::Nested::Request>();
    auto response = std::make_shared<test_msgs::srv::Nested::Response>();
    request->primitive_values = *primitive_msg;
    response->primitive_values = *primitive_msg;
    service_pairs.emplace_back(request, response);
  }
  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::DynamicArrayPrimitivesNested::Request::SharedPtr,
    test_msgs::srv::DynamicArrayPrimitivesNested::Response::SharedPtr
  >
>
get_services_dynamic_array_primitives_nested()
{
  std::vector<
    std::pair<
      test_msgs::srv::DynamicArrayPrimitivesNested::Request::SharedPtr,
      test_msgs::srv::DynamicArrayPrimitivesNested::Response::SharedPtr
    >
  > service_pairs;
  auto dynamic_array_primitive_msgs = get_messages_dynamic_array_primitives();
  auto request = std::make_shared<test_msgs::srv::DynamicArrayPrimitivesNested::Request>();
  auto response = std::make_shared<test_msgs::srv::DynamicArrayPrimitivesNested::Response>();
  for (size_t i = 0; i < dynamic_array_primitive_msgs.size(); ++i) {
    request->dynamic_array_primitive_values.push_back(*dynamic_array_primitive_msgs[i]);
    response->dynamic_array_primitive_values.push_back(*dynamic_array_primitive_msgs[i]);
  }
  service_pairs.emplace_back(request, response);
  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::DynamicArrayNested::Request::SharedPtr,
    test_msgs::srv::DynamicArrayNested::Response::SharedPtr
  >
>
get_services_dynamic_array_nested()
{
  std::vector<
    std::pair<
      test_msgs::srv::DynamicArrayNested::Request::SharedPtr,
      test_msgs::srv::DynamicArrayNested::Response::SharedPtr
    >
  > service_pairs;

  {
    auto request = std::make_shared<test_msgs::srv::DynamicArrayNested::Request>();
    auto response = std::make_shared<test_msgs::srv::DynamicArrayNested::Response>();

    auto primitive_msgs = get_messages_primitives();
    for (auto primitive_msg : primitive_msgs) {
      request->primitive_values.push_back(*primitive_msg);
      response->primitive_values.push_back(*primitive_msg);
    }
    service_pairs.emplace_back(request, response);
  }
  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::BoundedArrayNested::Request::SharedPtr,
    test_msgs::srv::BoundedArrayNested::Response::SharedPtr
  >
>
get_services_bounded_array_nested()
{
  std::vector<
    std::pair<
      test_msgs::srv::BoundedArrayNested::Request::SharedPtr,
      test_msgs::srv::BoundedArrayNested::Response::SharedPtr
    >
  > service_pairs;

  {
    auto request = std::make_shared<test_msgs::srv::BoundedArrayNested::Request>();
    auto response = std::make_shared<test_msgs::srv::BoundedArrayNested::Response>();

    auto primitive_msgs = get_messages_primitives();

    request->primitive_values.resize(primitive_msgs.size());
    response->primitive_values.resize(primitive_msgs.size());

    size_t i = 0;
    for (auto primitive_msg : primitive_msgs) {
      request->primitive_values[i] = *primitive_msg;
      response->primitive_values[i] = *primitive_msg;
      ++i;
    }
    service_pairs.emplace_back(request, response);
  }
  return service_pairs;
}

std::vector<
  std::pair<
    test_msgs::srv::StaticArrayNested::Request::SharedPtr,
    test_msgs::srv::StaticArrayNested::Response::SharedPtr
  >
>
get_services_static_array_nested()
{
  std::vector<
    std::pair<
      test_msgs::srv::StaticArrayNested::Request::SharedPtr,
      test_msgs::srv::StaticArrayNested::Response::SharedPtr
    >
  > service_pairs;

  {
    auto request = std::make_shared<test_msgs::srv::StaticArrayNested::Request>();
    auto response = std::make_shared<test_msgs::srv::StaticArrayNested::Response>();

    auto primitive_msgs = get_messages_primitives();
    assert(primitive_msgs.size() == request->primitive_values.size());
    assert(primitive_msgs.size() == response->primitive_values.size());
    size_t i = 0;
    for (auto primitive_msg : primitive_msgs) {
      request->primitive_values[i] = *primitive_msg;
      response->primitive_values[i] = *primitive_msg;
      ++i;
    }
    service_pairs.emplace_back(request, response);
  }
  return service_pairs;
}

#endif  // TEST_MSGS__SERVICE_FIXTURES_HPP_
