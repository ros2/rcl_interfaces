# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from test_msgs.message_fixtures import get_msg_dynamic_array_primitives
from test_msgs.message_fixtures import get_msg_primitives
from test_msgs.message_fixtures import int_from_uint

from test_msgs.srv import BoundedArrayNested
from test_msgs.srv import BoundedArrayPrimitives
from test_msgs.srv import DynamicArrayNested
from test_msgs.srv import DynamicArrayPrimitives
from test_msgs.srv import DynamicArrayPrimitivesNested
from test_msgs.srv import Empty
from test_msgs.srv import Nested
from test_msgs.srv import Primitives
from test_msgs.srv import StaticArrayNested
from test_msgs.srv import StaticArrayPrimitives


def get_srv_empty():
    req = Empty.Request()
    resp = Empty.Response()

    return [[req, resp]]


def get_srv_primitives():
    srvs = []

    req = Primitives.Request()
    resp = Primitives.Response()
    req.bool_value = False
    req.byte_value = bytes([0])
    req.char_value = '\x00'
    req.float32_value = float(0.0)
    req.float64_value = float(0.0)
    req.int8_value = 0
    req.uint8_value = 0
    req.int16_value = 0
    req.uint16_value = 0
    req.int32_value = 0
    req.uint32_value = 0
    req.int64_value = 0
    req.uint64_value = 0
    req.string_value = 'request'
    resp = Primitives.Response()
    resp.bool_value = False
    resp.byte_value = bytes([0])
    resp.char_value = '\x00'
    resp.float32_value = float(0.0)
    resp.float64_value = float(0.0)
    resp.int8_value = 0
    resp.uint8_value = 0
    resp.int16_value = 0
    resp.uint16_value = 0
    resp.int32_value = 0
    resp.uint32_value = 0
    resp.int64_value = 0
    resp.uint64_value = 0
    resp.string_value = 'reply'
    srvs.append([req, resp])

    req = Primitives.Request()
    req.bool_value = True
    req.byte_value = bytes([1])
    req.char_value = '\x01'
    req.float32_value = float(1.125)
    req.float64_value = float(1.125)
    req.int8_value = 1
    req.uint8_value = 2
    req.int16_value = 3
    req.uint16_value = 4
    req.int32_value = 5
    req.uint32_value = 6
    req.int64_value = 7
    req.uint64_value = 8
    # check strings longer then 256 characters
    req.string_value = ''
    for i in range(20000):
        req.string_value += str(i % 10)
    resp = Primitives.Response()
    resp.bool_value = True
    resp.byte_value = bytes([11])
    resp.char_value = '\x11'
    resp.float32_value = float(11.125)
    resp.float64_value = float(11.125)
    resp.int8_value = 11
    resp.uint8_value = 22
    resp.int16_value = 33
    resp.uint16_value = 44
    resp.int32_value = 55
    resp.uint32_value = 66
    resp.int64_value = 77
    resp.uint64_value = 88
    # check strings longer then 256 characters
    resp.string_value = ''
    for i in range(20000):
        resp.string_value += str(i % 10)
    srvs.append([req, resp])
    return srvs


def get_srv_static_array_primitives():
    srvs = []

    req = StaticArrayPrimitives.Request()
    resp = StaticArrayPrimitives.Response()

    req.bool_values = [False, True, False]
    req.byte_values = [bytes([0]), bytes([0xff]), bytes([0])]
    req.char_values = ['\x00', '\x7f', '\x00']
    req.float32_values = [0.0, 11.125, -22.125]
    req.float64_values = [0.0, 11.125, -22.125]
    req.int8_values = [0, 2**7 - 1, -2**7]
    req.uint8_values = [0, 2**8 - 1, 0]
    req.int16_values = [0, 2**15 - 1, -2**15]
    req.uint16_values = [0, 2**16 - 1, 0]
    req.int32_values = [0, 2**31 - 1, -2**31]
    req.uint32_values = [0, 2**32 - 1, 0]
    req.int64_values = [0, 2**63 - 1, -2**63]
    req.uint64_values = [0, 2**64 - 1, 0]
    req.string_values = ['', 'max value', 'min value']

    resp.bool_values = [True, False, True]
    resp.byte_values = [bytes([1]), bytes([0]), bytes([1])]
    resp.char_values = ['\x7f', '\x00', '\x7f']
    resp.float32_values = [0.0, -11.125, 22.125]
    resp.float64_values = [0.0, -11.125, 22.125]
    resp.int8_values = [2**7 - 1, -2**7, 0]
    resp.uint8_values = [2**8 - 1, 0, 2**8 - 1]
    resp.int16_values = [2**15 - 1, -2**15, 0]
    resp.uint16_values = [2**16 - 1, 0, 2**16 - 1]
    resp.int32_values = [2**31 - 1, -2**31, 0]
    resp.uint32_values = [2**32 - 1, 0, 2**32 - 1]
    resp.int64_values = [2**63 - 1, -2**63, 0]
    resp.uint64_values = [2**64 - 1, 0, 2**64 - 1]
    resp.string_values = ['max value', 'min value', '']

    srvs.append([req, resp])
    return srvs


def get_srv_bounded_array_primitives():
    srvs = []

    req = BoundedArrayPrimitives.Request()
    resp = BoundedArrayPrimitives.Response()

    req.bool_values = []
    req.byte_values = []
    req.char_values = []
    req.float32_values = []
    req.float64_values = []
    req.int8_values = []
    req.uint8_values = []
    req.int16_values = []
    req.uint16_values = []
    req.int32_values = []
    req.uint32_values = []
    req.int64_values = []
    req.uint64_values = []
    req.string_values = []
    req.check = 0

    resp.bool_values = [True]
    resp.byte_values = [bytes([255])]
    resp.char_values = ['\x7f']
    resp.float32_values = [1.125]
    resp.float64_values = [1.125]
    resp.int8_values = [2**7 - 1]
    resp.uint8_values = [2**8 - 1]
    resp.int16_values = [2**15 - 1]
    resp.uint16_values = [2**16 - 1]
    resp.int32_values = [2**31 - 1]
    resp.uint32_values = [2**32 - 1]
    resp.int64_values = [2**63 - 1]
    resp.uint64_values = [2**64 - 1]
    resp.string_values = ['max value']
    req.check = 1

    srvs.append([req, resp])

    req = BoundedArrayPrimitives.Request()
    resp = BoundedArrayPrimitives.Response()

    req.bool_values = [False, True, False]
    req.byte_values = [bytes([0]), bytes([0x01]), bytes([0xff])]
    req.char_values = ['\x00', '\x01', '\x7f']
    req.float32_values = [0.0, 1.125, -2.125]
    req.float64_values = [0.0, 1.125, -2.125]
    req.int8_values = [0, 2**7 - 1, -2**7]
    req.uint8_values = [0, 1, 2**8 - 1]
    req.int16_values = [0, 2**15 - 1, -2**15]
    req.uint16_values = [0, 1, 2**16 - 1]
    req.int32_values = [0, 2**31 - 1, -2**31]
    req.uint32_values = [0, 1, 2**32 - 1]
    req.int64_values = [0, 2**63 - 1, -2**63]
    req.uint64_values = [0, 1, 2**64 - 1]
    req.string_values = ['', 'max value', 'optional min value']
    req.check = 2

    resp.bool_values = [True, False, True]
    resp.byte_values = [bytes([255]), bytes([10]), bytes([11])]
    resp.char_values = ['\x7f', '\x0A', '\x0B']
    resp.float32_values = [-22.125, 0.0, -11.125]
    resp.float64_values = [-22.125, 0.0, -11.125]
    resp.int8_values = [-2**7, 0, 2**7 - 1]
    resp.uint8_values = [2**8 - 1, 0, 1]
    resp.int16_values = [-2**15, 0, 2**15 - 1]
    resp.uint16_values = [2**16 - 1, 0, 1]
    resp.int32_values = [-2**31, 0, 2**31 - 1]
    resp.uint32_values = [2**32 - 1, 0, 1]
    resp.int64_values = [-2**63, 0, 2**63 - 1]
    resp.uint64_values = [2**64 - 1, 0, 1]
    resp.string_values = ['optional min value', '', 'max value']
    resp.check = 3

    srvs.append([req, resp])

    return srvs


def get_srv_dynamic_array_primitives():
    srvs = []

    req = DynamicArrayPrimitives.Request()
    resp = DynamicArrayPrimitives.Response()

    req.bool_values = []
    req.byte_values = []
    req.char_values = []
    req.float32_values = []
    req.float64_values = []
    req.int8_values = []
    req.uint8_values = []
    req.int16_values = []
    req.uint16_values = []
    req.int32_values = []
    req.uint32_values = []
    req.int64_values = []
    req.uint64_values = []
    req.string_values = []

    resp.bool_values = [True]
    resp.byte_values = [bytes([255])]
    resp.char_values = ['\x7f']
    resp.float32_values = [1.125]
    resp.float64_values = [1.125]
    resp.int8_values = [2**7 - 1]
    resp.uint8_values = [2**8 - 1]
    resp.int16_values = [2**15 - 1]
    resp.uint16_values = [2**16 - 1]
    resp.int32_values = [2**31 - 1]
    resp.uint32_values = [2**32 - 1]
    resp.int64_values = [2**63 - 1]
    resp.uint64_values = [2**64 - 1]
    resp.string_values = ['max value']

    srvs.append([req, resp])

    req = BoundedArrayPrimitives.Request()
    resp = BoundedArrayPrimitives.Response()

    req.bool_values = [False, True]
    req.byte_values = [bytes([0]), bytes([0xff])]
    req.char_values = ['\x00', '\x7f']
    req.float32_values = [0.0, 1.125, -2.125]
    req.float64_values = [0.0, 1.125, -2.125]
    req.int8_values = [0, 2**7 - 1, -2**7]
    req.uint8_values = [0, 2**8 - 1]
    req.int16_values = [0, 2**15 - 1, -2**15]
    req.uint16_values = [0, 2**16 - 1]
    req.int32_values = [0, 2**31 - 1, -2**31]
    req.uint32_values = [0, 2**32 - 1]
    req.int64_values = [0, 2**63 - 1, -2**63]
    req.uint64_values = [0, 2**64 - 1]
    req.string_values = ['', 'max value', 'optional min value']

    size = 10000
    resp.bool_values = [i % 2 != 0 for i in range(size)]
    resp.byte_values = [bytes([i % (1 << 8)]) for i in range(size)]
    # TODO(mikaelarguedas) only ascii chars supported across languages
    resp.char_values = [chr(i % (1 << 7)) for i in range(size)]
    resp.float32_values = [float(1.125 * i) for i in range(size)]
    resp.float64_values = [1.125 * i for i in range(size)]
    resp.int8_values = [int_from_uint(i, 8) for i in range(size)]
    resp.uint8_values = [i % (1 << 8) for i in range(size)]
    resp.int16_values = [int_from_uint(i, 16) for i in range(size)]
    resp.uint16_values = [i % (1 << 16) for i in range(size)]
    resp.int32_values = [int_from_uint(i, 32) for i in range(size)]
    resp.uint32_values = [i % (1 << 32) for i in range(size)]
    resp.int64_values = [int_from_uint(i, 64) for i in range(size)]
    resp.uint64_values = [i % (1 << 64) for i in range(size)]
    resp.string_values = [str(i) for i in range(size)]

    srvs.append([req, resp])

    return srvs


def get_srv_dynamic_array_primitives_nested():
    srvs = []
    dynamic_array_primitives_msgs = get_msg_dynamic_array_primitives()

    req = DynamicArrayPrimitivesNested.Request()
    resp = DynamicArrayPrimitivesNested.Response()
    # for dynamic_array_primitives_msg in dynamic_array_primitives_msgs:
    for i in range(len(dynamic_array_primitives_msgs)):
        req.dynamic_array_primitive_values.append(dynamic_array_primitives_msgs[i])
        resp.dynamic_array_primitive_values.append(dynamic_array_primitives_msgs[i])
    srvs.append([req, resp])
    return srvs


def get_srv_nested():
    srvs = []
    primitives_msgs = get_msg_primitives()

    for primitive_msg in primitives_msgs:
        req = Nested.Request()
        req.primitive_values = primitive_msg

        resp = Nested.Response()
        resp.primitive_values = primitive_msg
        srvs.append([req, resp])
    return srvs


def get_srv_dynamic_array_nested():
    srvs = []
    primitives_msgs = get_msg_primitives()

    req = DynamicArrayNested.Request()
    resp = DynamicArrayNested.Response()
    for primitive_msg in primitives_msgs:
        req.primitive_values.append(primitive_msg)
        resp.primitive_values.append(primitive_msg)
    srvs.append([req, resp])
    return srvs


def get_srv_static_array_nested():
    srvs = []
    primitives_msgs = get_msg_primitives()
    i = 0

    req = StaticArrayNested.Request()
    resp = StaticArrayNested.Response()
    for primitive_msg in primitives_msgs:
        req.primitive_values[i] = primitive_msg
        resp.primitive_values[i] = primitive_msg
    srvs.append([req, resp])
    return srvs


def get_srv_bounded_array_nested():
    srvs = []
    primitives_msgs = get_msg_primitives()

    req = BoundedArrayNested.Request()
    resp = BoundedArrayNested.Response()
    for primitive_msg in primitives_msgs:
        req.primitive_values.append(primitive_msg)
        resp.primitive_values.append(primitive_msg)
    srvs.append([req, resp])
    return srvs


def get_test_srv(service_name):
    if 'Empty' == service_name:
        srv = get_srv_empty()
    elif 'Primitives' == service_name:
        srv = get_srv_primitives()
    elif 'Nested' == service_name:
        srv = get_srv_nested()
    elif 'StaticArrayNested' == service_name:
        srv = get_srv_static_array_nested()
    elif 'StaticArrayPrimitives' == service_name:
        srv = get_srv_static_array_primitives()
    # elif 'DynamicArrayPrimitives' == message_name:
    #     msg = get_msg_dynamic_array_primitives()
    elif 'DynamicArrayNested' == service_name:
        srv = get_srv_dynamic_array_nested()
    elif 'DynamicArrayPrimitivesNested' == service_name:
        srv = get_srv_dynamic_array_primitives_nested()
    elif 'BoundedArrayPrimitives' == service_name:
        srv = get_srv_bounded_array_primitives()
    elif 'BoundedArrayNested' == service_name:
        srv = get_srv_bounded_array_nested()
    else:
        raise NotImplementedError('%s service is not part of the test suite', service_name)
    return srv
