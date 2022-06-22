# The type of event this message represents
# See ServiceEventType for possible values
uint8 event_type

# Timestamp for when the event occurred (sent or received time)
builtin_interfaces/Time stamp

# Unique identifier for the client that sent the service request
# Note, this is only unique for the current session
unique_identifier_msgs/UUID client_id

# Sequence number for the request
# Combined with the client ID, this creates a unique ID for the service transaction
int64 sequence_number

string service_name
string request_type_name
string response_type_name
byte[] serialized_request
byte[] serialized_response
