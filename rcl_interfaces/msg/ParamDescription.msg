# This is the message to communicate a parameter.
# It is an open struct with an enum to select which value is active.

uint8 BOOL_PARAM=1
uint8 INTEGER_PARAM=2
uint8 DOUBLE_PARAM=3
uint8 STRING_PARAM=4

string name
uint8 param_type
