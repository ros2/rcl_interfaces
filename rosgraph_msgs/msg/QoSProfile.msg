# Message-based representation of ROS 2 Quality of Service settings
# Default values are kept in sync with RMW by integration test

# Depth of the message queue (only meaningful when history==KEEP_LAST)
uint32 depth

# Deadline between messages (0 for no deadline)
builtin_interfaces/Duration deadline

# Lifespan of each message (0 for infinite)
builtin_interfaces/Duration lifespan

# History policy
uint8 HISTORY_SYSTEM_DEFAULT=0
uint8 HISTORY_KEEP_LAST=1
uint8 HISTORY_KEEP_ALL=2
uint8 HISTORY_UNKNOWN=3
uint8 history

# Reliability policy
uint8 RELIABILITY_SYSTEM_DEFAULT=0
uint8 RELIABILITY_RELIABLE=1
uint8 RELIABILITY_BEST_EFFORT=2
uint8 RELIABILITY_UNKNOWN=3
uint8 reliability

# Durability policy
uint8 DURABILITY_SYSTEM_DEFAULT=0
uint8 DURABILITY_TRANSIENT_LOCAL=1
uint8 DURABILITY_VOLATILE=2
uint8 DURABILITY_UNKNOWN=3
uint8 durability

# Liveliness policy
uint8 LIVELINESS_SYSTEM_DEFAULT=0
uint8 LIVELINESS_AUTOMATIC=1
uint8 LIVELINESS_MANUAL_BY_TOPIC=3
uint8 LIVELINESS_UNKNOWN=4
uint8 liveliness

# Lease duration for liveliness (0 for infinite)
builtin_interfaces/Duration liveliness_lease_duration
