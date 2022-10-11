# Represents the type of a field and related meta-data.

# A constant for each type supported according to:
#   http://design.ros2.org/articles/legacy_interface_definition.html
# and:
#   http://design.ros2.org/articles/idl_interface_definition.html
# Order is loosely coupled to the order of appearance in the IDL 4.2 spec:
#  https://www.omg.org/spec/IDL/4.2

# Layout of constants across the 0-255 decimal values in the uint8:
#
# - 000-031: Primitive types, strings, and reserved space for future primitive types
# - 032-063: Fixed sized array of primitive and string types
# - 064-095: Bounded Sequences of primitive and string types
# - 096-127: Unbounded Sequences of primitive and string types
# - 128-255: Reserved space for future array/sequence-like types

# Nested type defined in other .msg/.idl files.
uint8 FIELD_TYPE_NESTED_TYPE = 0

# Basic Types
# Integer Types
uint8 FIELD_TYPE_INT8 = 1
uint8 FIELD_TYPE_UINT8 = 2
uint8 FIELD_TYPE_INT16 = 3
uint8 FIELD_TYPE_UINT16 = 4
uint8 FIELD_TYPE_INT32 = 5
uint8 FIELD_TYPE_UINT32 = 6
uint8 FIELD_TYPE_INT64 = 7
uint8 FIELD_TYPE_UINT64 = 8

# Floating-Point Types
uint8 FIELD_TYPE_FLOAT = 9
uint8 FIELD_TYPE_DOUBLE = 10
uint8 FIELD_TYPE_LONG_DOUBLE = 11

# Char and WChar Types
uint8 FIELD_TYPE_CHAR = 12
uint8 FIELD_TYPE_WCHAR = 13

# Boolean Type
uint8 FIELD_TYPE_BOOLEAN = 14

# Byte/Octet Type
uint8 FIELD_TYPE_BYTE = 15

# String Types
uint8 FIELD_TYPE_STRING = 16
uint8 FIELD_TYPE_WSTRING = 17

# Fixed String Types
uint8 FIELD_TYPE_FIXED_STRING = 18
uint8 FIELD_TYPE_FIXED_WSTRING = 19

# Bounded String Types
uint8 FIELD_TYPE_BOUNDED_STRING = 20
uint8 FIELD_TYPE_BOUNDED_WSTRING = 21

# Fixed Sized Array Types
uint8 FIELD_TYPE_NESTED_TYPE_ARRAY = 32
uint8 FIELD_TYPE_INT8_ARRAY = 33
uint8 FIELD_TYPE_UINT8_ARRAY = 34
uint8 FIELD_TYPE_INT16_ARRAY = 35
uint8 FIELD_TYPE_UINT16_ARRAY = 36
uint8 FIELD_TYPE_INT32_ARRAY = 37
uint8 FIELD_TYPE_UINT32_ARRAY = 38
uint8 FIELD_TYPE_INT64_ARRAY = 39
uint8 FIELD_TYPE_UINT64_ARRAY = 40
uint8 FIELD_TYPE_FLOAT_ARRAY = 41
uint8 FIELD_TYPE_DOUBLE_ARRAY= 42
uint8 FIELD_TYPE_LONG_DOUBLE_ARRAY= 43
uint8 FIELD_TYPE_CHAR_ARRAY= 44
uint8 FIELD_TYPE_WCHAR_ARRAY= 45
uint8 FIELD_TYPE_BOOLEAN_ARRAY= 46
uint8 FIELD_TYPE_BYTE_ARRAY= 47
uint8 FIELD_TYPE_STRING_ARRAY= 48
uint8 FIELD_TYPE_WSTRING_ARRAY= 49
uint8 FIELD_TYPE_FIXED_STRING_ARRAY = 50
uint8 FIELD_TYPE_FIXED_WSTRING_ARRAY = 51
uint8 FIELD_TYPE_BOUNDED_STRING_ARRAY = 52
uint8 FIELD_TYPE_BOUNDED_WSTRING_ARRAY = 53

# Bounded Sequence Types
uint8 FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE = 64
uint8 FIELD_TYPE_INT8_BOUNDED_SEQUENCE = 65
uint8 FIELD_TYPE_UINT8_BOUNDED_SEQUENCE = 66
uint8 FIELD_TYPE_INT16_BOUNDED_SEQUENCE = 67
uint8 FIELD_TYPE_UINT16_BOUNDED_SEQUENCE = 68
uint8 FIELD_TYPE_INT32_BOUNDED_SEQUENCE = 69
uint8 FIELD_TYPE_UINT32_BOUNDED_SEQUENCE = 70
uint8 FIELD_TYPE_INT64_BOUNDED_SEQUENCE = 71
uint8 FIELD_TYPE_UINT64_BOUNDED_SEQUENCE = 72
uint8 FIELD_TYPE_FLOAT_BOUNDED_SEQUENCE = 73
uint8 FIELD_TYPE_DOUBLE_BOUNDED_SEQUENCE = 74
uint8 FIELD_TYPE_LONG_DOUBLE_BOUNDED_SEQUENCE = 75
uint8 FIELD_TYPE_CHAR_BOUNDED_SEQUENCE = 76
uint8 FIELD_TYPE_WCHAR_BOUNDED_SEQUENCE = 77
uint8 FIELD_TYPE_BOOLEAN_BOUNDED_SEQUENCE = 78
uint8 FIELD_TYPE_BYTE_BOUNDED_SEQUENCE = 79
uint8 FIELD_TYPE_STRING_BOUNDED_SEQUENCE = 80
uint8 FIELD_TYPE_WSTRING_BOUNDED_SEQUENCE = 81
uint8 FIELD_TYPE_FIXED_STRING_BOUNDED_SEQUENCE = 82
uint8 FIELD_TYPE_FIXED_WSTRING_BOUNDED_SEQUENCE = 83
uint8 FIELD_TYPE_BOUNDED_STRING_BOUNDED_SEQUENCE = 84
uint8 FIELD_TYPE_BOUNDED_WSTRING_BOUNDED_SEQUENCE = 85

# Unbounded Sequence Types
uint8 FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE = 96
uint8 FIELD_TYPE_INT8_UNBOUNDED_SEQUENCE = 97
uint8 FIELD_TYPE_UINT8_UNBOUNDED_SEQUENCE = 98
uint8 FIELD_TYPE_INT16_UNBOUNDED_SEQUENCE = 99
uint8 FIELD_TYPE_UINT16_UNBOUNDED_SEQUENCE = 100
uint8 FIELD_TYPE_INT32_UNBOUNDED_SEQUENCE = 101
uint8 FIELD_TYPE_UINT32_UNBOUNDED_SEQUENCE = 102
uint8 FIELD_TYPE_INT64_UNBOUNDED_SEQUENCE = 103
uint8 FIELD_TYPE_UINT64_UNBOUNDED_SEQUENCE = 104
uint8 FIELD_TYPE_FLOAT_UNBOUNDED_SEQUENCE = 105
uint8 FIELD_TYPE_DOUBLE_UNBOUNDED_SEQUENCE = 106
uint8 FIELD_TYPE_LONG_DOUBLE_UNBOUNDED_SEQUENCE = 107
uint8 FIELD_TYPE_CHAR_UNBOUNDED_SEQUENCE = 108
uint8 FIELD_TYPE_WCHAR_UNBOUNDED_SEQUENCE = 109
uint8 FIELD_TYPE_BOOLEAN_UNBOUNDED_SEQUENCE = 110
uint8 FIELD_TYPE_BYTE_UNBOUNDED_SEQUENCE = 111
uint8 FIELD_TYPE_STRING_UNBOUNDED_SEQUENCE = 112
uint8 FIELD_TYPE_WSTRING_UNBOUNDED_SEQUENCE = 113
uint8 FIELD_TYPE_FIXED_STRING_UNBOUNDED_SEQUENCE = 114
uint8 FIELD_TYPE_FIXED_WSTRING_UNBOUNDED_SEQUENCE = 115
uint8 FIELD_TYPE_BOUNDED_STRING_UNBOUNDED_SEQUENCE = 116
uint8 FIELD_TYPE_BOUNDED_WSTRING_UNBOUNDED_SEQUENCE = 117

# Identifying number for the type of the field, using one of the above constants.
uint8 type_id

# Only used when the type is an array or a bounded sequence.
# In the case of an array, this is the fixed length of the array.
# In the case of a bounded sequence, this is the maximum size of the sequence.
# In all other cases this field is unused.
uint64 length

# Only used when the type is a fixed or bounded string/wstring, or a array/sequence of those.
# In the case of a fixed string/wstring, it is the fixed length of the string.
# In the case of a bounded string/wstring, it is the maximum length of the string.
# In the case of an array/sequence of fixed string/wstring, it is the fixed length of the strings.
# In the case of an array/sequence of bounded string/wstring, it is the maximum length of the strings.
# It is not currently possible to have different string lengths per element in the array/sequences.
uint64 string_length

# Only used when the type is a nested type or array/sequence of nested types.
string nested_type_name
