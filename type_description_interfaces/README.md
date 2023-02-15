# type_description_interfaces

A package containing message and service definitions for describing and communicating descriptions of other types.

## Messages (.msg)

* [Field](msg/Field.msg): Represents a single field in a ROS Interface Type
* [FieldType](msg/FieldType.msg): Represents the type of a single field in a ROS Interface Type
* [IndividualTypeDescription](msg/IndividualTypeDescription.msg): Represents a single ROS Message Type by itself
* [TypeDescription](msg/TypeDescription.msg): Represents a single ROS Message Type along with all referenced types

## Quality Declaration

This package claims to be in the **Quality Level 1** category, see the [Quality Declaration](QUALITY_DECLARATION.md) for more details.

## TODO

* Do we (will we) support fixed sized strings vs. just having bounded strings?
* Should we pick limits (bounds) for strings in these types, e.g. type names, default values, etc?
* Should we pick limits (bounds) for sequences in these types, e.g. number of referenced types?
