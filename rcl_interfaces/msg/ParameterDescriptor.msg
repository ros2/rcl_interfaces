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

# If this bounded sequence contains a floating_point_range constraint it must
# be enforced. FloatingPointRange consist of a from_value a to_value and a step.
# FloatingPointRange and IntegerRange are mutually exclusive
FloatingPointRange[<=1] floating_point_range

# If this bounded sequence contains a integer_range constraint it must
# be enforced. IntegerRange consist of a from_value a to_value and a step.
# FloatingPointRange and IntegerRange are mutually exclusive
IntegerRange[<=1] integer_range

# more constraints to follow in the future...
