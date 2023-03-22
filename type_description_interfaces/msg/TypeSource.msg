# Represents the original source of a ROS 2 interface definition.

# ROS interface type name, in PACKAGE/NAMESPACE/TYPENAME format.
string type_name

# The type of the original source file, typically matching the file extension.
# Well-known encodings: "idl", "msg", "srv", "action", "dynamic".
string encoding

# Dumped contents of the interface definition source file.
# If this was a type created programmatically (encoding "dynamic"), this field will be empty.
string raw_file_contents
