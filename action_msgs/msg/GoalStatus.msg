# An action goal can be in one of these states after it is accepted by an action server.
# For more information, see http://design.ros2.org/articles/actions.html
uint8 STATUS_ACCEPTED  = 0
uint8 STATUS_EXECUTING = 1
uint8 STATUS_CANCELING = 2
uint8 STATUS_SUCCEEDED = 3
uint8 STATUS_CANCELED  = 4
uint8 STATUS_ABORTED   = 5

# Goal ID
# TODO(jacobperron): Use a ported version of https://github.com/ros-geographic-info/unique_identifier/blob/master/uuid_msgs
UUID goal_id

# Time when the goal was accepted
builtin_interfaces/Time stamp

# Goal status
uint8 status
