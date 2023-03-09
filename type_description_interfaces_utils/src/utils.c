// Copyright 2023 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// NOTE(methylDragon): Maybe this belongs inside the type_description_interfaces
//                     package instead?
//                     But as a C header (.h)???

// NOTE(methylDragon): I made it so that every instance of a non-message struct (e.g. hash map)
//                     borrows, whereas the message structs copy.
//                     So lifetime should be managed by the message structs.

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <type_description_interfaces_utils/utils.h>

#include <rcutils/logging_macros.h>
#include <rcutils/qsort.h>
#include <rcutils/types/rcutils_ret.h>
#include <rcutils/types/hash_map.h>
#include <rosidl_runtime_c/string_functions.h>

#include <type_description_interfaces/msg/field.h>
#include <type_description_interfaces/msg/individual_type_description.h>
#include <type_description_interfaces/msg/type_description.h>


// =================================================================================================
// GET BY NAME
// =================================================================================================

rcutils_ret_t
type_description_interfaces_utils_find_field(
  const type_description_interfaces__msg__Field__Sequence * fields,
  const char * name,
  type_description_interfaces__msg__Field ** field)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(fields, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(name, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(field, RCUTILS_RET_INVALID_ARGUMENT);
  if (*field != NULL) {
    RCUTILS_LOG_ERROR("`field` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  for (size_t i = 0; i < fields->size; i++) {
    if (strcmp(fields->data[i].name.data, name) == 0) {
      *field = &fields->data[i];
      return RCUTILS_RET_OK;
    }
  }

  RCUTILS_LOG_WARN("Could not find field: %s", name);
  return RCUTILS_RET_NOT_FOUND;
}


rcutils_ret_t
type_description_interfaces_utils_find_referenced_type_description(
  const type_description_interfaces__msg__IndividualTypeDescription__Sequence * referenced_types,
  const char * type_name,
  type_description_interfaces__msg__IndividualTypeDescription ** referenced_type)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(referenced_types, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_name, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(referenced_type, RCUTILS_RET_INVALID_ARGUMENT);
  if (*referenced_type != NULL) {
    RCUTILS_LOG_ERROR("`referenced_type` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  for (size_t i = 0; i < referenced_types->size; i++) {
    if (strcmp(referenced_types->data[i].type_name.data, type_name) == 0) {
      *referenced_type = &referenced_types->data[i];
      return RCUTILS_RET_OK;
    }
  }

  RCUTILS_LOG_WARN("Could not find referenced type description: %s", type_name);
  return RCUTILS_RET_NOT_FOUND;
}


// =================================================================================================
// HASH MAPS
// =================================================================================================

rcutils_ret_t
type_description_interfaces_utils_get_field_map(
  const type_description_interfaces__msg__IndividualTypeDescription * individual_description,
  const rcutils_allocator_t * allocator,
  rcutils_hash_map_t ** hash_map)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(individual_description, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocator, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(hash_map, RCUTILS_RET_INVALID_ARGUMENT);
  if (*hash_map != NULL) {
    RCUTILS_LOG_ERROR("`hash_map` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  rcutils_hash_map_t * out = allocator->allocate(sizeof(rcutils_hash_map_t), allocator->state);
  if (out == NULL) {
    RCUTILS_LOG_ERROR("Could not allocate output hash map");
    return RCUTILS_RET_BAD_ALLOC;
  }
  *out = rcutils_get_zero_initialized_hash_map();

  rcutils_ret_t ret = RCUTILS_RET_ERROR;
  rcutils_ret_t fail_ret = RCUTILS_RET_ERROR;

  ret = rcutils_hash_map_init(
    out, individual_description->fields.size,
    sizeof(char *), sizeof(type_description_interfaces__msg__Field *),
    rcutils_hash_map_string_hash_func, rcutils_hash_map_string_cmp_func,
    allocator);
  if (ret != RCUTILS_RET_OK) {
    allocator->deallocate(out, allocator->state);
    RCUTILS_LOG_ERROR("Could not init hash map");
    return ret;
  }

  for (size_t i = 0; i < individual_description->fields.size; i++) {
    type_description_interfaces__msg__Field * tmp = &individual_description->fields.data[i];
    // Passing tmp is fine even if tmp goes out of scope later since it copies in the set method...
    ret = rcutils_hash_map_set(out, &individual_description->fields.data[i].name.data, &tmp);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR(
        "Could not set hash map entry for field: %s",
        individual_description->fields.data[i].name.data);
      fail_ret = ret;
      goto fail;
    }
  }

  *hash_map = out;
  return RCUTILS_RET_OK;

fail:
  {
    rcutils_ret_t fini_ret = rcutils_hash_map_fini(out);
    if (fini_ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Failed to finalize hash map");
    }
    allocator->deallocate(out, allocator->state);
  }
  return fail_ret;
}


rcutils_ret_t
type_description_interfaces_utils_get_referenced_type_description_map(
  const type_description_interfaces__msg__IndividualTypeDescription__Sequence * referenced_types,
  const rcutils_allocator_t * allocator,
  rcutils_hash_map_t ** hash_map)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(referenced_types, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocator, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(hash_map, RCUTILS_RET_INVALID_ARGUMENT);
  if (*hash_map != NULL) {
    RCUTILS_LOG_ERROR("`hash_map` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  rcutils_hash_map_t * out = allocator->allocate(sizeof(rcutils_hash_map_t), allocator->state);
  if (out == NULL) {
    RCUTILS_LOG_ERROR("Could not allocate output hash map");
    return RCUTILS_RET_BAD_ALLOC;
  }
  *out = rcutils_get_zero_initialized_hash_map();

  rcutils_ret_t ret = RCUTILS_RET_ERROR;
  rcutils_ret_t fail_ret = RCUTILS_RET_ERROR;

  ret = rcutils_hash_map_init(
    out, referenced_types->size,
    sizeof(char *), sizeof(type_description_interfaces__msg__IndividualTypeDescription *),
    rcutils_hash_map_string_hash_func, rcutils_hash_map_string_cmp_func,
    allocator);
  if (ret != RCUTILS_RET_OK) {
    allocator->deallocate(out, allocator->state);
    RCUTILS_LOG_ERROR("Could not init hash map");
    return ret;
  }

  for (size_t i = 0; i < referenced_types->size; i++) {
    type_description_interfaces__msg__IndividualTypeDescription * tmp = &referenced_types->data[i];
    // Passing tmp is fine even if tmp goes out of scope later since it copies in the set method...
    ret = rcutils_hash_map_set(out, &referenced_types->data[i].type_name.data, &tmp);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR(
        "Could not set hash map entry for referenced type: %s",
        referenced_types->data[i].type_name.data);
      fail_ret = ret;
      goto fail;
    }
  }

  size_t map_length;
  ret = rcutils_hash_map_get_size(out, &map_length);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not get size of hash map for validation");
    fail_ret = RCUTILS_RET_ERROR;
    goto fail;
  }

  if (referenced_types->size != map_length) {  // Duplicate referenced types is invalid
    RCUTILS_LOG_ERROR("Passed referenced IndividualTypeDescriptions has duplicate types");
    fail_ret = RCUTILS_RET_INVALID_ARGUMENT;
    goto fail;
  }

  *hash_map = out;
  return RCUTILS_RET_OK;

fail:
  {
    rcutils_ret_t fini_ret = rcutils_hash_map_fini(out);
    if (fini_ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Failed to finalize hash map");
    }
    allocator->deallocate(out, allocator->state);
  }
  return fail_ret;
}


// =================================================================================================
// DESCRIPTION VALIDITY
// =================================================================================================

rcutils_ret_t
type_description_interfaces_utils_get_necessary_referenced_type_descriptions_map(
  const type_description_interfaces__msg__IndividualTypeDescription * main_type_description,
  const rcutils_hash_map_t * referenced_types_map,
  const rcutils_allocator_t * allocator,
  rcutils_hash_map_t ** seen_map)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(main_type_description, RCUTILS_RET_INVALID_ARGUMENT);
  HASH_MAP_VALIDATE_HASH_MAP(referenced_types_map);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(allocator, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(seen_map, RCUTILS_RET_INVALID_ARGUMENT);

  // Only true for the top level call, so we can determine when to finalize the map
  bool top_level_call = false;
  rcutils_ret_t ret = RCUTILS_RET_ERROR;
  rcutils_ret_t fail_ret = RCUTILS_RET_ERROR;

  // 1. Init new hash map only on the top level call
  if (!*seen_map) {
    top_level_call = true;

    *seen_map = allocator->allocate(sizeof(rcutils_hash_map_t), allocator->state);
    if (*seen_map == NULL) {
      RCUTILS_LOG_ERROR("Could not allocate hash map");
      return RCUTILS_RET_BAD_ALLOC;
    }
    **seen_map = rcutils_get_zero_initialized_hash_map();

    size_t referenced_types_map_size;
    ret = rcutils_hash_map_get_size(referenced_types_map, &referenced_types_map_size);
    if (ret != RCUTILS_RET_OK) {
      allocator->deallocate(*seen_map, allocator->state);
      RCUTILS_LOG_ERROR("Could not get size of referenced types hash map");
      *seen_map = NULL;
      return RCUTILS_RET_ERROR;
    }

    ret = rcutils_hash_map_init(
      *seen_map, referenced_types_map_size,
      sizeof(char *), sizeof(type_description_interfaces__msg__IndividualTypeDescription *),
      rcutils_hash_map_string_hash_func, rcutils_hash_map_string_cmp_func,
      allocator);
    if (ret != RCUTILS_RET_OK) {
      allocator->deallocate(*seen_map, allocator->state);
      RCUTILS_LOG_ERROR("Could not init hash map");
      *seen_map = NULL;
      return RCUTILS_RET_BAD_ALLOC;
    }
  }

  // 2. Iterate through fields
  for (size_t i = 0; i < main_type_description->fields.size; i++) {
    type_description_interfaces__msg__Field * field = &main_type_description->fields.data[i];
    // 3. Skip cases
    // continue if field is not nested type or nested type is in seen map:
    if ((field->type.type_id % TYPE_DESCRIPTION_INTERFACES_UTILS_SEQUENCE_TYPE_ID_DELIMITER) != 1 ||
      rcutils_hash_map_key_exists(*seen_map, field->type.nested_type_name.data))
    {
      continue;
    }

    // 4. Error cases
    // Referenced type does not exist
    if (!rcutils_hash_map_key_exists(referenced_types_map, field->type.nested_type_name.data)) {
      RCUTILS_LOG_ERROR("Missing referenced type: %s", field->type.nested_type_name.data);
      fail_ret = RCUTILS_RET_NOT_FOUND;
      goto fail;
    }
    // Nested name empty
    if (field->type.nested_type_name.size == 0) {
      RCUTILS_LOG_ERROR("Missing referenced type name");
      fail_ret = RCUTILS_RET_INVALID_ARGUMENT;
      goto fail;
    }

    // 5. Add to seen map (we didn't skip and didn't error out)
    type_description_interfaces__msg__IndividualTypeDescription * necessary_description;
    ret = rcutils_hash_map_get(
      *seen_map, field->type.nested_type_name.data, &necessary_description);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR(
        "Couldn't get necessary referenced type: %s", field->type.nested_type_name.data);
      fail_ret = ret;  // Most likely a RCUTILS_RET_NOT_FOUND
      goto fail;
    }

    // Check for mismatched name
    if (strcmp(field->type.nested_type_name.data, necessary_description->type_name.data) != 0) {
      RCUTILS_LOG_ERROR(
        "Necessary referenced type name (%s) did not match field's nested type name (%s)",
        necessary_description->type_name.data,
        field->type.nested_type_name.data);
      fail_ret = RCUTILS_RET_INVALID_ARGUMENT;
      goto fail;
    }

    // Add to map (finally!!)
    ret = rcutils_hash_map_set(
      *seen_map, &field->type.nested_type_name.data, necessary_description);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Failed to set hash map for key: %s", field->type.nested_type_name.data);
      fail_ret = ret;
      goto fail;
    }

    // Recurse on fields on necessary_description
    ret = type_description_interfaces_utils_get_necessary_referenced_type_descriptions_map(
      necessary_description, referenced_types_map, allocator, seen_map);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Recursion failed on: %s", necessary_description->type_name.data);
      fail_ret = ret;
      goto fail;
    }
  }  // End field iteration

  return RCUTILS_RET_OK;

fail:
  if (top_level_call) {
    rcutils_ret_t fini_ret = rcutils_hash_map_fini(*seen_map);
    if (fini_ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Failed to finalize hash map");
    }
    allocator->deallocate(*seen_map, allocator->state);
    *seen_map = NULL;
  }
  return fail_ret;
}


rcutils_ret_t
type_description_interfaces_utils_copy_init_sequence_from_referenced_type_descriptions_map(
  const rcutils_hash_map_t * hash_map,
  type_description_interfaces__msg__IndividualTypeDescription__Sequence ** sequence)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(hash_map, RCUTILS_RET_INVALID_ARGUMENT);
  if (*sequence != NULL) {
    RCUTILS_LOG_ERROR("`sequence` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  size_t map_length;
  rcutils_ret_t ret = RCUTILS_RET_ERROR;
  ret = rcutils_hash_map_get_size(hash_map, &map_length);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not get size of hash map");
    return RCUTILS_RET_ERROR;
  }
  *sequence = type_description_interfaces__msg__IndividualTypeDescription__Sequence__create(
    map_length);
  if (*sequence == NULL) {
    RCUTILS_LOG_ERROR("Could allocate sequence");
    return RCUTILS_RET_BAD_ALLOC;
  }

  size_t i = 0;
  char * key;
  type_description_interfaces__msg__IndividualTypeDescription * data;
  rcutils_ret_t status = rcutils_hash_map_get_next_key_and_data(hash_map, NULL, &key, &data);
  while (RCUTILS_RET_OK == status) {
    if (strcmp(key, data->type_name.data) != 0) {
      RCUTILS_LOG_ERROR(
        "Necessary referenced type name (%s) did not match key (%s)", data->type_name.data, key);
      type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(*sequence);
      return RCUTILS_RET_INVALID_ARGUMENT;
    }

    // Deep copy
    if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
        data, &((*sequence)->data[i])))
    {
      RCUTILS_LOG_ERROR("Could not copy type %s to sequence", key);
      type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(*sequence);
      return RCUTILS_RET_BAD_ALLOC;
    }

    i += 1;
    status = rcutils_hash_map_get_next_key_and_data(hash_map, &key, &key, &data);
  }

  return RCUTILS_RET_OK;
}


int
type_description_interfaces_utils_referenced_type_description_sequence_sort_compare(
  const void * lhs, const void * rhs)
{
  type_description_interfaces__msg__IndividualTypeDescription * left =
    *(type_description_interfaces__msg__IndividualTypeDescription **)lhs;
  type_description_interfaces__msg__IndividualTypeDescription * right =
    *(type_description_interfaces__msg__IndividualTypeDescription **)rhs;
  if (left == NULL) {
    return right == NULL ? 0 : 1;
  } else if (right == NULL) {
    return -1;
  }
  return strcmp(left->type_name.data, right->type_name.data);
}


rcutils_ret_t
type_description_interfaces_utils_sort_referenced_type_descriptions_in_place(
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * sequence)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(sequence, RCUTILS_RET_INVALID_ARGUMENT);
  return rcutils_qsort(
    sequence->data,
    sequence->size,
    sizeof(sequence->data[0]),
    type_description_interfaces_utils_referenced_type_description_sequence_sort_compare);
}


rcutils_ret_t
type_description_interfaces_utils_prune_referenced_type_descriptions_in_place(
  const type_description_interfaces__msg__IndividualTypeDescription * main_type_description,
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * referenced_types)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(main_type_description, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(referenced_types, RCUTILS_RET_INVALID_ARGUMENT);

  rcutils_ret_t ret = RCUTILS_RET_ERROR;
  rcutils_ret_t end_ret = RCUTILS_RET_ERROR;

  rcutils_hash_map_t * referenced_types_map = NULL;
  rcutils_hash_map_t * seen_map = NULL;
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  ret = type_description_interfaces_utils_get_referenced_type_description_map(
    referenced_types, &allocator, &referenced_types_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not construct referenced type description map");
    return ret;
  }

  ret = type_description_interfaces_utils_get_necessary_referenced_type_descriptions_map(
    main_type_description, referenced_types_map, &allocator, &seen_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not construct necessary referenced type description map");
    return ret;
  }

  size_t map_length;
  ret = rcutils_hash_map_get_size(seen_map, &map_length);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not get size of hash map for validation");
    end_ret = RCUTILS_RET_ERROR;
    goto end;
  }
  // End early if pruning was not needed
  if ((referenced_types)->size == map_length) {
    end_ret = RCUTILS_RET_OK;
    goto end;
  }

  // Otherwise, we need to rearrange and resize the sequence
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * out =
    type_description_interfaces__msg__IndividualTypeDescription__Sequence__create(map_length);

  // First obtain all necessary types
  size_t append_count = 0;
  for (size_t i = 0; i < referenced_types->size; i++) {
    if (rcutils_hash_map_key_exists(seen_map, referenced_types->data[i].type_name.data)) {
      // Transfer ownership of necessary referenced types from input sequence to output sequence,
      // NOTE(methylDragon): We can't just swap the sequence elements with NULL since they're
      //                     values, not pointers...
      out->data[append_count++] = referenced_types->data[i];
    } else {
      // Deleting unnecessary referenced types otherwise
      type_description_interfaces__msg__IndividualTypeDescription__destroy(
        &referenced_types->data[i]);
    }
  }

  // Then rearrange the input referenced types sequence
  for (size_t i = 0; i < append_count; i++) {
    // This is a deep copy, so we don't need to worry about managing pointers in the rearrange
    if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
        &out->data[i], &referenced_types->data[i]))
    {
      RCUTILS_LOG_ERROR(
        "Could not copy necessary referenced type description sequence during rearrangement! "
        "Beware! The referenced type descriptions was likely already partially modified in place!");
      end_ret = RCUTILS_RET_ERROR;
      type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(out);
      goto end;
    }
  }
  // Delete entries after the section of necessary referenced types, and shrink the input sequence
  for (size_t i = append_count; i < referenced_types->size; i++) {
    type_description_interfaces__msg__IndividualTypeDescription__destroy(
      &referenced_types->data[i]);
  }
  if (allocator.reallocate(referenced_types->data, append_count, allocator.state) == NULL) {
    RCUTILS_LOG_ERROR(
      "Could not shrink the necessary referenced type descriptions sequence during rearrangement! "
      "Beware! The referenced type descriptions was likely already partially modified in place!");
    end_ret = RCUTILS_RET_BAD_ALLOC;
    type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(out);
    goto end;
  }
  referenced_types->size = append_count;
  referenced_types->capacity = append_count;

  type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(out);
  end_ret = RCUTILS_RET_OK;

end:
  {
    rcutils_ret_t fini_ret = rcutils_hash_map_fini(seen_map);
    if (fini_ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Failed to finalize hash map");
    }
    allocator.deallocate(seen_map, allocator.state);
  }

  return end_ret;
}


bool
type_description_interfaces_utils_field_is_valid(type_description_interfaces__msg__Field * field)
{
  if (field == NULL) {
    RCUTILS_LOG_WARN("Field is invalid: Pointer is null");
    return false;
  }
  if (field->name.size == 0) {
    RCUTILS_LOG_WARN("Field is invalid: Empty name");
    return false;
  }
  if ((field->type.type_id % TYPE_DESCRIPTION_INTERFACES_UTILS_SEQUENCE_TYPE_ID_DELIMITER) != 0) {
    RCUTILS_LOG_WARN("Field `%s` is invalid: Unset type ID", field->name.data);
    return false;
  }
  if ((field->type.type_id % TYPE_DESCRIPTION_INTERFACES_UTILS_SEQUENCE_TYPE_ID_DELIMITER) == 1 &&
    field->type.nested_type_name.size == 0)
  {
    RCUTILS_LOG_WARN(
      "Field `%s` is invalid: Field is nested but with empty nested type name", field->name.data);
    return false;
  }
  return true;
}


bool
type_description_interfaces_utils_individual_type_description_is_valid(
  type_description_interfaces__msg__IndividualTypeDescription * description)
{
  if (description == NULL) {
    RCUTILS_LOG_WARN("Individual type description is invalid: Pointer is null");
    return false;
  }
  if (description->type_name.size == 0) {
    RCUTILS_LOG_WARN("Individual type description is invalid: Empty name");
    return false;
  }

  for (size_t i = 0; i < description->fields.size; i++) {
    if (!type_description_interfaces_utils_field_is_valid(&description->fields.data[i])) {
      RCUTILS_LOG_WARN(
        "Individual type description `%s` is invalid: Invalid field", description->type_name.data);
      return false;
    }
  }

  bool end_ret = false;
  rcutils_hash_map_t * hash_map = NULL;
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  rcutils_ret_t ret = type_description_interfaces_utils_get_field_map(
    description, &allocator, &hash_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not construct field map for validation");
    return false;
  }

  size_t map_length;
  ret = rcutils_hash_map_get_size(hash_map, &map_length);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not get size of field map for validation");
    goto end;
  }

  if (description->fields.size != map_length) {
    RCUTILS_LOG_WARN(
      "Individual type description `%s` is invalid: Duplicate fields", description->type_name.data);
    goto end;
  }

  end_ret = true;

end:
  {
    rcutils_ret_t fini_ret = rcutils_hash_map_fini(hash_map);
    if (fini_ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_ERROR("Failed to finalize hash map");
    }
    allocator.deallocate(hash_map, allocator.state);
    return end_ret;
  }
}


bool
type_description_interfaces_utils_type_description_is_valid(
  type_description_interfaces__msg__TypeDescription * description)
{
  if (description == NULL) {
    RCUTILS_LOG_WARN("Type description is invalid: Pointer is null");
    return false;
  }

  if (!type_description_interfaces_utils_individual_type_description_is_valid(
      &description->type_description))
  {
    if (description->type_description.type_name.size != 0) {
      RCUTILS_LOG_WARN(
        "Type description `%s` is invalid: Main type description is invalid",
        description->type_description.type_name.data);
    } else {
      RCUTILS_LOG_WARN("Type description is invalid: Main type description is invalid");
    }
    return false;
  }

  bool end_ret = false;
  rcutils_hash_map_t * referenced_types_map = NULL;
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  rcutils_ret_t ret = type_description_interfaces_utils_get_referenced_type_description_map(
    &description->referenced_type_descriptions, &allocator, &referenced_types_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not construct referenced type description map");
    return false;
  }

  size_t map_length;

  // Check no duplicated ref types
  ret = rcutils_hash_map_get_size(referenced_types_map, &map_length);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not get size of referenced type description map for validation");
    goto end_ref;
  }
  if (description->referenced_type_descriptions.size != map_length) {
    RCUTILS_LOG_WARN(
      "Type description `%s` is invalid: Duplicate referenced type descriptions",
      description->type_description.type_name.data);
    goto end_ref;
  }

  // Check no missing necessary ref types
  rcutils_hash_map_t * necessary_types_map = NULL;
  ret = type_description_interfaces_utils_get_necessary_referenced_type_descriptions_map(
    &description->type_description, referenced_types_map, &allocator, &necessary_types_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not construct necessary referenced type description map");
    goto end_ref;
  }

  // Check no unnecessary ref types
  ret = rcutils_hash_map_get_size(necessary_types_map, &map_length);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR(
      "Could not get size of necessary referenced type description map for validation");
    goto end_necessary;
  }

  if (description->referenced_type_descriptions.size != map_length) {
    RCUTILS_LOG_WARN(
      "Type description `%s` is invalid: Unnecessary referenced type descriptions",
      description->type_description.type_name.data);
    goto end_necessary;
  }

  // Check all referenced types valid (the prior checks ensure all of them are necessary)
  for (size_t i = 0; i < description->referenced_type_descriptions.size; i++) {
    if (!type_description_interfaces_utils_individual_type_description_is_valid(
        &description->referenced_type_descriptions.data[i]))
    {
      RCUTILS_LOG_WARN(
        "Type description `%s` is invalid: Invalid referenced type description",
        description->type_description.type_name.data);
      goto end_necessary;
    }
  }

  // Check referenced types sorted
  type_description_interfaces__msg__IndividualTypeDescription__Sequence * sorted_sequence =
    type_description_interfaces__msg__IndividualTypeDescription__Sequence__create(map_length);
  if (sorted_sequence == NULL) {
    RCUTILS_LOG_ERROR("Could allocate sequence for copy of referenced type descriptions");
    goto end_necessary;
  }
  if (type_description_interfaces__msg__IndividualTypeDescription__Sequence__copy(
      &description->referenced_type_descriptions, sorted_sequence))
  {
    RCUTILS_LOG_ERROR("Could not copy referenced type descriptions for validation");
    goto end_sequence;
  }
  ret = type_description_interfaces_utils_sort_referenced_type_descriptions_in_place(
    sorted_sequence);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not sort copy of referenced type descriptions for validation");
    goto end_sequence;
  }

  if (!type_description_interfaces__msg__IndividualTypeDescription__Sequence__are_equal(
      &description->referenced_type_descriptions, sorted_sequence))
  {
    RCUTILS_LOG_WARN(
      "Type description `%s` is invalid: Referenced type descriptions not sorted",
      description->type_description.type_name.data);
    goto end_sequence;
  }

  end_ret = true;

end_sequence:
  type_description_interfaces__msg__IndividualTypeDescription__Sequence__destroy(sorted_sequence);

end_necessary:
  ret = rcutils_hash_map_fini(necessary_types_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Failed to finalize referenced types map");
  }
  allocator.deallocate(necessary_types_map, allocator.state);

end_ref:
  ret = rcutils_hash_map_fini(referenced_types_map);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Failed to finalize referenced types map");
  }
  allocator.deallocate(referenced_types_map, allocator.state);

  return end_ret;
}


rcutils_ret_t
type_description_interfaces_utils_coerce_to_valid_type_description_in_place(
  type_description_interfaces__msg__TypeDescription * type_description)
{
  if (!type_description_interfaces_utils_individual_type_description_is_valid(
      &type_description->type_description))
  {
    RCUTILS_LOG_ERROR("Could not make type description valid: Invalid main type description");
    return RCUTILS_RET_ERROR;
  }

  rcutils_ret_t ret;
  ret = type_description_interfaces_utils_prune_referenced_type_descriptions_in_place(
    &type_description->type_description, &type_description->referenced_type_descriptions);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_WARN(
      "Could not make type description valid: Could not prune referenced_type_descriptions");
    return ret;
  }

  ret = type_description_interfaces_utils_sort_referenced_type_descriptions_in_place(
    &type_description->referenced_type_descriptions);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_WARN(
      "Could not make type description valid: Could not sort referenced_type_descriptions");
    return ret;
  }

  return RCUTILS_RET_OK;
}


// =================================================================================================
// DESCRIPTION CONSTRUCTION
// =================================================================================================

rcutils_ret_t
type_description_interfaces_utils_create_field(
  const char * name, size_t name_length,
  uint8_t type_id, uint64_t capacity, uint64_t string_capacity,
  const char * nested_type_name, size_t nested_type_name_length,
  const char * default_value, size_t default_value_length,
  type_description_interfaces__msg__Field ** field)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(name, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(nested_type_name, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(default_value, RCUTILS_RET_INVALID_ARGUMENT);
  if (*field != NULL) {
    RCUTILS_LOG_ERROR("`field` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  *field = type_description_interfaces__msg__Field__create();

  // Field
  if (!rosidl_runtime_c__String__assignn(&(*field)->name, name, name_length)) {
    RCUTILS_LOG_ERROR("Could not assign field name");
    type_description_interfaces__msg__Field__destroy(*field);
    *field = NULL;
    return RCUTILS_RET_BAD_ALLOC;
  }
  if (!rosidl_runtime_c__String__assignn(
      &(*field)->default_value, default_value, default_value_length))
  {
    RCUTILS_LOG_ERROR("Could not assign field default value");
    type_description_interfaces__msg__Field__destroy(*field);
    *field = NULL;
    return RCUTILS_RET_BAD_ALLOC;
  }

  // FieldType
  (*field)->type.type_id = type_id;
  (*field)->type.capacity = capacity;
  (*field)->type.string_capacity = string_capacity;

  if (!rosidl_runtime_c__String__assignn(
      &(*field)->type.nested_type_name, nested_type_name, nested_type_name_length))
  {
    RCUTILS_LOG_ERROR("Could not assign field nested type name");
    type_description_interfaces__msg__Field__destroy(*field);
    *field = NULL;
    return RCUTILS_RET_BAD_ALLOC;
  }

  return RCUTILS_RET_OK;
}


rcutils_ret_t
type_description_interfaces_utils_create_individual_type_description(
  const char * type_name, size_t type_name_length,
  type_description_interfaces__msg__IndividualTypeDescription ** individual_description)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_name, RCUTILS_RET_INVALID_ARGUMENT);
  if (*individual_description != NULL) {
    RCUTILS_LOG_ERROR("`individual_description` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  *individual_description = type_description_interfaces__msg__IndividualTypeDescription__create();

  if (!rosidl_runtime_c__String__assignn(
      &(*individual_description)->type_name, type_name, type_name_length))
  {
    RCUTILS_LOG_ERROR("Could not assign individual description type name");
    type_description_interfaces__msg__IndividualTypeDescription__destroy(*individual_description);
    *individual_description = NULL;
    return RCUTILS_RET_BAD_ALLOC;
  }
  return RCUTILS_RET_OK;
}


rcutils_ret_t
type_description_interfaces_utils_create_type_description(
  const char * type_name, size_t type_name_length,
  type_description_interfaces__msg__TypeDescription ** type_description)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_name, RCUTILS_RET_INVALID_ARGUMENT);
  if (*type_description != NULL) {
    RCUTILS_LOG_ERROR("`type_description` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  *type_description = type_description_interfaces__msg__TypeDescription__create();

  if (!rosidl_runtime_c__String__assignn(
      &(*type_description)->type_description.type_name, type_name, type_name_length))
  {
    RCUTILS_LOG_ERROR("Could not assign main individual description type name");
    type_description_interfaces__msg__TypeDescription__destroy(*type_description);
    *type_description = NULL;
    return RCUTILS_RET_BAD_ALLOC;
  }
  return RCUTILS_RET_OK;
}


rcutils_ret_t
type_description_interfaces_utils_append_field(
  type_description_interfaces__msg__IndividualTypeDescription * individual_type_description,
  type_description_interfaces__msg__Field * field)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(individual_type_description, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(field, RCUTILS_RET_INVALID_ARGUMENT);

  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcutils_ret_t fini_ret = RCUTILS_RET_ERROR;

  size_t allocation_size = (
    (individual_type_description->fields.size + 1) *
    sizeof(type_description_interfaces__msg__Field)
  );
  type_description_interfaces__msg__Field * next_ptr = allocator.reallocate(
    individual_type_description->fields.data, allocation_size, allocator.state);
  if (next_ptr == NULL) {
    RCUTILS_LOG_ERROR("Could not realloc individual type description fields sequence");
    return RCUTILS_RET_BAD_ALLOC;
  }

  if (!type_description_interfaces__msg__Field__init(next_ptr)) {
    RCUTILS_LOG_ERROR("Could not init new individual type description field element");
    fini_ret = RCUTILS_RET_BAD_ALLOC;
    goto fail;
  }

  if (!type_description_interfaces__msg__Field__copy(field, next_ptr)) {
    RCUTILS_LOG_ERROR("Could not copy into new individual type description field element");
    type_description_interfaces__msg__Field__fini(next_ptr);
    fini_ret = RCUTILS_RET_ERROR;
    goto fail;
  }

  individual_type_description->fields.data = next_ptr;
  individual_type_description->fields.size += 1;
  individual_type_description->fields.capacity += 1;
  return RCUTILS_RET_OK;

fail:
  next_ptr = allocator.reallocate(
    individual_type_description->fields.data,
    individual_type_description->fields.size,
    allocator.state);
  if (next_ptr == NULL) {
    RCUTILS_LOG_ERROR(
      "Could not shorten individual type description fields sequence. "
      "Excess memory will be UNINITIALIZED!");
    individual_type_description->fields.size += 1;
    individual_type_description->fields.capacity += 1;
  }
  return fini_ret;
}


rcutils_ret_t
type_description_interfaces_utils_append_referenced_individual_type_description(
  type_description_interfaces__msg__TypeDescription * type_description,
  type_description_interfaces__msg__IndividualTypeDescription * referenced_type_description,
  bool sort)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_description, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(referenced_type_description, RCUTILS_RET_INVALID_ARGUMENT);

  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  type_description_interfaces__msg__IndividualTypeDescription * next_ptr = allocator.reallocate(
    type_description->referenced_type_descriptions.data,
    type_description->referenced_type_descriptions.size + 1,
    allocator.state);
  if (next_ptr == NULL) {
    RCUTILS_LOG_ERROR("Could not realloc type description referenced type descriptions sequence");
    return RCUTILS_RET_BAD_ALLOC;
  }

  if (!type_description_interfaces__msg__IndividualTypeDescription__init(next_ptr)) {
    RCUTILS_LOG_ERROR("Could not init new type description referenced type descriptions element");
    return RCUTILS_RET_BAD_ALLOC;
  }

  if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
      referenced_type_description, next_ptr))
  {
    // Attempt to undo changes on failure
    RCUTILS_LOG_ERROR(
      "Could not copy into new type description referenced type descriptions element");
    type_description_interfaces__msg__IndividualTypeDescription__fini(next_ptr);
    next_ptr = allocator.reallocate(
      type_description->referenced_type_descriptions.data,
      type_description->referenced_type_descriptions.size,
      allocator.state);
    if (next_ptr == NULL) {
      RCUTILS_LOG_ERROR(
        "Could not shorten type description referenced type descriptions sequence. "
        "Excess memory will be UNINITIALIZED!");
      type_description->referenced_type_descriptions.size += 1;
      type_description->referenced_type_descriptions.capacity += 1;
    }
    return RCUTILS_RET_ERROR;
  }

  if (sort) {
    rcutils_ret_t ret =
      type_description_interfaces_utils_sort_referenced_type_descriptions_in_place(
      &type_description->referenced_type_descriptions);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_WARN("Could not sort copy of referenced type descriptions for validation");
    }
  }

  type_description->referenced_type_descriptions.size += 1;
  type_description->referenced_type_descriptions.capacity += 1;
  return RCUTILS_RET_OK;
}


rcutils_ret_t
type_description_interfaces_utils_append_referenced_type_description(
  type_description_interfaces__msg__TypeDescription * type_description,
  type_description_interfaces__msg__TypeDescription * type_description_to_append,
  bool coerce_to_valid)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_description, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(type_description_to_append, RCUTILS_RET_INVALID_ARGUMENT);
  if (coerce_to_valid &&
    !type_description_interfaces_utils_type_description_is_valid(type_description_to_append))
  {
    RCUTILS_LOG_ERROR(
      "`type_description_to_append` is invalid, it must be valid if `coerce_to_valid is true`");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcutils_ret_t fini_ret = RCUTILS_RET_ERROR;

  // +1 for the type_description_to_append's main type description
  size_t extend_size = type_description_to_append->referenced_type_descriptions.size + 1;
  type_description_interfaces__msg__IndividualTypeDescription * next_ptr = allocator.reallocate(
    type_description->referenced_type_descriptions.data,
    type_description->referenced_type_descriptions.size + extend_size,
    allocator.state);
  if (next_ptr == NULL) {
    RCUTILS_LOG_ERROR("Could not realloc type description referenced type descriptions sequence");
    return RCUTILS_RET_BAD_ALLOC;
  }

  size_t init_reset_size = 0;
  for (size_t i = 0; i < extend_size; i++) {
    if (!type_description_interfaces__msg__IndividualTypeDescription__init(&next_ptr[i])) {
      RCUTILS_LOG_ERROR("Could not init new type description referenced type descriptions element");
      fini_ret = RCUTILS_RET_BAD_ALLOC;
      goto fail;
    }
    init_reset_size += 1;
  }

  // Copy type_description_to_append's main type description
  if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
      &type_description_to_append->type_description, next_ptr))
  {
    RCUTILS_LOG_ERROR(
      "Could not copy into new type description referenced type descriptions element");
    fini_ret = RCUTILS_RET_ERROR;
    goto fail;
  }

  // Copy type_description_to_append's referenced type descriptions
  // There are (extend_size - 1) referenced type descriptions to copy
  for (size_t i = 1; i < extend_size; i++) {
    if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
        &type_description_to_append->referenced_type_descriptions.data[i - 1], &next_ptr[i]))
    {
      RCUTILS_LOG_ERROR("Could not init new type description referenced type descriptions element");
      fini_ret = RCUTILS_RET_BAD_ALLOC;
      goto fail;
    }
    init_reset_size += 1;
  }

  type_description->referenced_type_descriptions.size += extend_size;
  type_description->referenced_type_descriptions.capacity += extend_size;

  if (coerce_to_valid) {
    rcutils_ret_t ret =
      type_description_interfaces_utils_coerce_to_valid_type_description_in_place(type_description);
    if (ret != RCUTILS_RET_OK) {
      RCUTILS_LOG_WARN("Could not coerce type description to valid!");
      return RCUTILS_RET_WARN;
    }
  }

  return RCUTILS_RET_OK;

fail:
  // Attempt to undo changes on failure
  for (size_t j = 0; j < init_reset_size; j++) {
    type_description_interfaces__msg__IndividualTypeDescription__fini(&next_ptr[j]);
  }
  next_ptr = allocator.reallocate(
    type_description->referenced_type_descriptions.data,
    type_description->referenced_type_descriptions.size,
    allocator.state);
  if (next_ptr == NULL) {
    RCUTILS_LOG_ERROR(
      "Could not shorten type description referenced type descriptions sequence. "
      "Excess memory will be UNINITIALIZED!");
    type_description->referenced_type_descriptions.size += extend_size;
    type_description->referenced_type_descriptions.capacity += extend_size;
  }
  return fini_ret;
}


rcutils_ret_t
type_description_interfaces_utils_get_referenced_type_description_as_type_description(
  type_description_interfaces__msg__TypeDescription * parent_description,
  type_description_interfaces__msg__IndividualTypeDescription * referenced_description,
  type_description_interfaces__msg__TypeDescription ** output_description)
{
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(parent_description, RCUTILS_RET_INVALID_ARGUMENT);
  RCUTILS_CHECK_ARGUMENT_FOR_NULL(referenced_description, RCUTILS_RET_INVALID_ARGUMENT);
  if (*output_description != NULL) {
    RCUTILS_LOG_ERROR("`output_description` output argument is not pointing to null");
    return RCUTILS_RET_INVALID_ARGUMENT;
  }

  *output_description = type_description_interfaces__msg__TypeDescription__create();
  if (*output_description == NULL) {
    RCUTILS_LOG_ERROR("Could not create output type description");
    return RCUTILS_RET_BAD_ALLOC;
  }

  if (!type_description_interfaces__msg__IndividualTypeDescription__copy(
      referenced_description, &(*output_description)->type_description))
  {
    RCUTILS_LOG_ERROR("Could not copy referenced type description into main description");
    type_description_interfaces__msg__TypeDescription__destroy(*output_description);
    *output_description = NULL;
    return RCUTILS_RET_ERROR;
  }

  if (!type_description_interfaces__msg__IndividualTypeDescription__Sequence__copy(
      &parent_description->referenced_type_descriptions,
      &(*output_description)->referenced_type_descriptions))
  {
    RCUTILS_LOG_ERROR("Could not copy referenced type descriptions");
    type_description_interfaces__msg__TypeDescription__destroy(*output_description);
    *output_description = NULL;
    return RCUTILS_RET_ERROR;
  }

  rcutils_ret_t ret =
    type_description_interfaces_utils_coerce_to_valid_type_description_in_place(*output_description);
  if (ret != RCUTILS_RET_OK) {
    RCUTILS_LOG_ERROR("Could not coerce output type description to valid");
    type_description_interfaces__msg__TypeDescription__destroy(*output_description);
    *output_description = NULL;
    return ret;
  }
  return RCUTILS_RET_OK;
}


// =================================================================================================
// DESCRIPTION PRINTING
// =================================================================================================

void
type_description_interfaces_utils_print_field_type(
  const type_description_interfaces__msg__FieldType * field_type)
{
  printf(
    "  [FIELD TYPE]\n"
    "    type_id: %d\n"
    "    capacity: %ld\n"
    "    string_capacity: %ld\n",
    field_type->type_id, field_type->capacity, field_type->string_capacity);

  if (field_type->nested_type_name.data == NULL) {
    printf("    nested_type_name: %s\n", field_type->nested_type_name.data);
  } else {
    printf("    nested_type_name: \"%s\"\n", field_type->nested_type_name.data);
  }
}


void
type_description_interfaces_utils_print_field(const type_description_interfaces__msg__Field * field)
{
  printf("[FIELD]\n");

  if (field->name.data == NULL) {
    printf("  name: %s\n", field->name.data);
  } else {
    printf("  name: \"%s\"\n", field->name.data);
  }

  if (field->default_value.data == NULL) {
    printf("  default_value: %s\n", field->default_value.data);
  } else {
    printf("  default_value: \"%s\"\n", field->default_value.data);
  }

  type_description_interfaces_utils_print_field_type(&field->type);
}


void
type_description_interfaces_utils_print_individual_type_description(
  const type_description_interfaces__msg__IndividualTypeDescription * individual_type_description)
{
  printf(
    "\n[INDIVIDUAL TYPE DESCRIPTION] (Fields: %ld)\n", individual_type_description->fields.size);

  if (individual_type_description->type_name.data == NULL) {
    printf("  type_name: %s\n", individual_type_description->type_name.data);
  } else {
    printf("  type_name: \"%s\"\n", individual_type_description->type_name.data);
  }

  for (size_t i = 0; i < individual_type_description->fields.size; i++) {
    type_description_interfaces_utils_print_field(&individual_type_description->fields.data[i]);
  }
}


void type_description_interfaces_utils_print_type_description(
  const type_description_interfaces__msg__TypeDescription * type_description)
{
  printf("\n\n---\n\n");

  printf(
    "= [PRINTING TYPE DESCRIPTION] = (Referenced descriptions: %ld)\n",
    type_description->referenced_type_descriptions.size);

  printf("\n== [MAIN DESCRIPTION] ==\n");
  type_description_interfaces_utils_print_individual_type_description(
    &type_description->type_description);

  printf("\n== [REFERENCED DESCRIPTIONS] ==\n");
  for (size_t i = 0; i < type_description->referenced_type_descriptions.size; i++) {
    type_description_interfaces_utils_print_individual_type_description(
      &type_description->referenced_type_descriptions.data[i]);
  }

  printf("\n---\n\n");
}


void
type_description_interfaces_utils_print_field_map(const rcutils_hash_map_t * hash_map)
{
  char * key;
  type_description_interfaces__msg__Field * data = NULL;
  rcutils_ret_t status = rcutils_hash_map_get_next_key_and_data(hash_map, NULL, &key, &data);
  while (RCUTILS_RET_OK == status) {
    if (key == NULL) {
      printf("== KEY: %s ==\n", key);
    } else {
      printf("== KEY: \"%s\" ==\n", key);
    }
    type_description_interfaces_utils_print_field(data);
    status = rcutils_hash_map_get_next_key_and_data(hash_map, &key, &key, &data);
  }
}


void
type_description_interfaces_utils_print_referenced_type_description_map(
  const rcutils_hash_map_t * hash_map)
{
  char * key;
  type_description_interfaces__msg__IndividualTypeDescription * data;
  rcutils_ret_t status = rcutils_hash_map_get_next_key_and_data(hash_map, NULL, &key, &data);
  while (RCUTILS_RET_OK == status) {
    if (key == NULL) {
      printf("== KEY: %s ==\n", key);
    } else {
      printf("== KEY: \"%s\" ==\n", key);
    }
    type_description_interfaces_utils_print_individual_type_description(data);
    status = rcutils_hash_map_get_next_key_and_data(hash_map, &key, &key, &data);
  }
}
