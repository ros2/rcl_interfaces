# A true value of the same index indicates that the parameter was set
# successfully. A false value indicates the change was rejected.
bool successful

# Reason why the setting was a failure. On success, the contents of this field
# are undefined.  This should only be used for logging and user interfaces.
string reason

# This reason for failing to set a parameter value should be given when the node
# is only allowed to set values for declared parameters, and the parameter that
# the request was trying to set not declared by the node. Use the ListParameters
# service to see which parameters are declared.
string REASON_UNDECLARED_NOT_ALLOWED = "parameter is not declared by the node, which only allows declared parameters"
