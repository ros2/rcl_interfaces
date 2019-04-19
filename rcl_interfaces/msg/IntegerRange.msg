# Represents bounds and a step value for an integer typed parameter.

# Lower bound for valid values, inclusive.
int64 minimum_value

# Upper bound for valid values, inclusive.
int64 maximum_value

# Size of valid steps between the lower and upper bound.
# Step should be positive, and a step of zero implies a step size of one, i.e.
# all integer values between the bounds are valid.
# Step size should be less than the distance between the minimum and maximum
# values, and ideally would be an even multiple of that distance, but that
# is not required.
int64 step
