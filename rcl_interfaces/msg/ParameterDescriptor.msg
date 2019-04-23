# This is the message to communicate a parameter's descriptor.

string name
uint8 type # Enum defined in ParameterType.msg
# If 'true' then the value cannot change after it has been initialized
bool read_only false

# TODO: add additional meta data
