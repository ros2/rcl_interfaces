# Duration defines a period between two time points. It is comprised of a
# seconds component and a nanoseconds component.

# Seconds component, range is valid over any possible int32 value.
int32 sec

# Nanoseconds component in the range of [0, 10e9).
uint32 nanosec
