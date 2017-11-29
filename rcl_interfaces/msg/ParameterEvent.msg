# This message contains a parameter event.
# It was an atomic update.
# A specific parameter name can only be in one of the three sets.

RclHeader rcl_header
# Name of the node that requested the parameter change
string node_req
Parameter[] new_parameters
Parameter[] changed_parameters
Parameter[] deleted_parameters
