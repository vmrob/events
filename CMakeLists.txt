cmake_minimum_required (VERSION 3.1)

enable_testing()

project (event-bus)

set(CONSTEXPR_INCLUDE ${CMAKE_SOURCE_DIR}/vendor/constexpr/src/include)

add_subdirectory (events)
add_subdirectory (examples)
add_subdirectory (vendor/googletest)
add_subdirectory (vendor/constexpr)
