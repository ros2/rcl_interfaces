# Represents the observable state of a ROS Node

# Node descriptor fields, which can describe a node that is not running

rcl_interfaces/ParameterDescriptor[] parameters
Topic[] publishers
Topic[] subscriptions

Service[] service_clients
Service[] service_servers

Action[] action_clients
Action[] action_servers

# Node state fields, which only apply to a running instance of a node

# Fully qualified node name (FQN)
string name

# Current parameter values
# parameter_values[] must be empty, or the same size as parameters[]
# When set, parameter_values[] match up 1:1 with the same index in parameters[]
rcl_interfaces/ParameterValue[] parameter_values
