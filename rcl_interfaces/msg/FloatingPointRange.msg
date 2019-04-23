# Represents bounds and a step value for a floating point typed parameter.

# Lower bound for valid values, inclusive.
double from_value

# Upper bound for valid values, inclusive.
double to_value

# Size of valid steps between the from and to bound.
# Step should be positive, and a step of zero implies continuous values.
# Step size should be less than the distance between the values, and ideally
# would be an even multiple of that distance, but that is not required.
double step
