# Represents bounds and a step value for a floating point typed parameter.

# Start value for valid values range, inclusive.
double from_value

# End value for valid values range, inclusive.
double to_value

# Size of valid steps between the from and to bound.
# Step should be positive, and a step of zero implies continuous values.
# Step size should be less than the distance between the values, and an even
# multiple of that distance.
double step
