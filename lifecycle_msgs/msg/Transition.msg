# Default values for transitions
# as described on
# http://design.ros2.org/articles/node_lifecycle.html

uint8 TRANSITION_CREATE     = 0
uint8 TRANSITION_CONFIGURE  = 1
uint8 TRANSITION_CLEANUP    = 2
uint8 TRANSITION_ACTIVATE   = 3
uint8 TRANSITION_DEACTIVATE = 4
uint8 TRANSITION_SHUTDOWN   = 5
uint8 TRANSITION_DESTROY    = 6

# Transition description
uint8 id
string label
