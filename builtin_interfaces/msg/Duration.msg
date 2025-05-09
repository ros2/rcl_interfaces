# Duration defines a period between two time points.
# Messages of this datatype are of ROS Time following this design:
# https://design.ros2.org/articles/clock_and_time.html

# The seconds component, valid over all int32 values.
int32 sec

<<<<<<< HEAD
# Nanoseconds component in the range of [0, 10e9).
=======
# The nanoseconds component, valid in the range [0, 1e9), to be added to the seconds component. 
# e.g.
# The duration -1.7 seconds is represented as {sec: -2, nanosec: 3e8}
# The duration 1.7 seconds is represented as {sec: 1, nanosec: 7e8}
>>>>>>> 355006b (Add info to duration message and time message comments (#176))
uint32 nanosec
