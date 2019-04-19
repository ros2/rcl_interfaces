# This is the message to communicate a parameter's descriptor.

string name

# Enum values are defined in the `ParameterType.msg` message.
uint8 type

# Parameter constraints

# If 'true' then the value cannot change after it has been initialized.
bool read_only false

# docs...
FloatingPointRange[<=1] floating_point_range

# docs...
IntegerRange[<=1] integer_range

# more constraints to follow in the future...
