# action_msgs
This package contains several messages and services useful for ROS 2 actions.
More information about actions can be found on its [design article](http://design.ros2.org/articles/actions.html).

For more information about ROS 2 interfaces, see [index.ros2.org](https://index.ros.org/doc/ros2/Concepts/About-ROS-Interfaces/)

## Messages (.msg)
* [GoalInfo](msg/GoalInfo.msg): Goal identifier message, with a goal id and time stamp
* [GoalStatus](msg/GoalStatus.msg): Describes a goal's current state machine status
* [GoalStatusArray](msg/GoalStatusArray.msg): An array of [GoalStatus](msg/GoalStatus.msg) messages

## Services (.srv)
* [CancelGoal](srv/CancelGoal.srv): Cancel Goals either by id and/or timestamp
