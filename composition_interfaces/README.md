# composition_interfaces
This is a package containing message and service definitions for managing composable nodes in a container process.
Generally these services are used by the ROS 2 [`roslaunch`](https://design.ros2.org/articles/roslaunch.html) system.

For more information about ROS 2 interfaces, see [index.ros2.org](https://index.ros.org/doc/ros2/Concepts/About-ROS-Interfaces/).

## Services (.srv)
* [ListNodes](srv/ListNodes.srv): Retrieve a list of running composable nodes, including their names and ids.
* [LoadNodes](srv/LoadNode.srv): Load a composable node.
* [UnloadNode](UnloadNode.srv): Unload a specified node by its id.

## Quality Declaration
This package claims to be in the **Quality Level 4** category, see the [Quality Declaration](QUALITY_DECLARATION.md) for more details.
