# This message contains descriptors of a parameter event.
# It was an atomic update.
# A specific parameter name can only be in one of the three sets.

RclHeader rcl_header
# Name of the node that requested the parameter change
string node_req
ParameterDescriptor[] new_parameters
ParameterDescriptor[] changed_parameters
ParameterDescriptor[] deleted_parameters
