cmake_minimum_required (VERSION 3.1)

enable_testing()

project (event-bus)

add_subdirectory (events)
add_subdirectory (examples)
add_subdirectory (vendor/googletest)
