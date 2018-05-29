# This is the message to communicate a parameter's descriptor.

string name
uint8 type # Enum defined in ParameterType.msg
# If 'false' then the value cannot change after it has been initialized
bool mutable_after_initialization true

# TODO: add additional meta data
