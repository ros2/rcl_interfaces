# Represents the original source of a ROS 2 interface definition.

uint8 ENCODING_NOT_SET = 0
uint8 ENCODING_MSG = 1
uint8 ENCODING_SRV = 2
uint8 ENCODING_ACTION = 3
uint8 ENCODING_IDL = 4

# ROS interface type name, in PACKAGE/NAMESPACE/TYPENAME format
string type_name

# The type of the original source file, from the above constants
uint8 encoding

# Dumped contents of the interface definition source file
string raw_file_contents
