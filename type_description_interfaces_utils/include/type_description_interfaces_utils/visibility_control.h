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

#ifndef TYPE_DESCRIPTION_INTERFACES_UTILS__VISIBILITY_CONTROL_H_
#define TYPE_DESCRIPTION_INTERFACES_UTILS__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_EXPORT __attribute__ ((dllexport))
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_IMPORT __attribute__ ((dllimport))
  #else
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_EXPORT __declspec(dllexport)
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_IMPORT __declspec(dllimport)
  #endif
  #ifdef TYPE_DESCRIPTION_INTERFACES_UTILS_BUILDING_DLL
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC TYPE_DESCRIPTION_INTERFACES_UTILS_EXPORT
  #else
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC TYPE_DESCRIPTION_INTERFACES_UTILS_IMPORT
  #endif
  #define TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC_TYPE TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC
  #define TYPE_DESCRIPTION_INTERFACES_UTILS_LOCAL
#else
  #define TYPE_DESCRIPTION_INTERFACES_UTILS_EXPORT __attribute__ ((visibility("default")))
  #define TYPE_DESCRIPTION_INTERFACES_UTILS_IMPORT
  #if __GNUC__ >= 4
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC __attribute__ ((visibility("default")))
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC
    #define TYPE_DESCRIPTION_INTERFACES_UTILS_LOCAL
  #endif
  #define TYPE_DESCRIPTION_INTERFACES_UTILS_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // TYPE_DESCRIPTION_INTERFACES_UTILS__VISIBILITY_CONTROL_H_
