cmake_minimum_required (VERSION 3.1)

enable_testing()

project (event-bus)

set (CMAKE_CXX_FLAGS "-std=c++14 -DNDEBUG -Wall -Werror -g -O3 ${CMAKE_CXX_FLAGS}")

set(CONSTEXPR_INCLUDE ${CMAKE_SOURCE_DIR}/vendor/constexpr/src/include)

add_subdirectory (events)
add_subdirectory (vendor/googletest)
add_subdirectory (vendor/benchmark)
add_subdirectory (vendor/constexpr)
