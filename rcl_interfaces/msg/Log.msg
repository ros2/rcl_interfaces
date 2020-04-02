##
## Severity level constants
## 
## These logging levels follow the Python Standard
## https://docs.python.org/3/library/logging.html#logging-levels
## And are implemented in rcutils as well
## https://github.com/ros2/rcutils/blob/35f29850064e0c33a4063cbc947ebbfeada11dba/include/rcutils/logging.h#L164-L172
## This leaves space for other logging levels to be inserted in the middle in the future.
## Since there are several other logging enumeration standard for different implementations.
## Other logging implementations may need to provide level translations to match their internal implementations.
##
byte DEBUG=10 #debug level
byte INFO=20  #general level
byte WARN=30  #warning level
byte ERROR=40 #error level
byte FATAL=50 #fatal/critical level

##
## Fields
##
builtin_interfaces/Time stamp
uint8 level
string name # the name representing the logger this message came from
string msg # message
string file # file the message came from
string function # function the message came from
uint32 line # line the message came from
