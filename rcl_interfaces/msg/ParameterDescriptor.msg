# This is the message to communicate a parameter's descriptor.

string name

# Enum values are defined in the `ParameterType.msg` message.
uint8 type

# Description of the parameter, visible from introspection tools.
string description

# Parameter constraints

# Plain English description of additional constraints which cannot be expressed
# with the available constraints, e.g. "only prime numbers".
# By convention, this should only be used to clarify constraints which cannot
# be completely expressed with the parameter constraints below.
string additional_constraints

# If 'true' then the value cannot change after it has been initialized.
bool read_only false

# docs...
FloatingPointRange[<=1] floating_point_range

# docs...
IntegerRange[<=1] integer_range

# more constraints to follow in the future...
