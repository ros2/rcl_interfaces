# This is the message to communicate a parameter.
# It is an open struct with an enum to select which value is active.

uint8 BOOL_PARAMETER=1
uint8 INTEGER_PARAMETER=2
uint8 DOUBLE_PARAMETER=3
uint8 STRING_PARAMETER=4
uint8 BYTES_PARAMETER=5

string name
uint8 parameter_type
