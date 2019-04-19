# This is the message to communicate a parameter's descriptor.

string name

# Enum values are defined in the `ParameterType.msg` message.
uint8 type

# If 'true' then the value cannot change after it has been initialized.
bool read_only false
