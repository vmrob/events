add_executable (examples src/main.cpp)
target_link_libraries (examples events)

set (CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
