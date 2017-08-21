set (CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")

add_library (events
  src/Publisher.cpp
)
target_include_directories(
  events
PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CONSTEXPR_INCLUDE}
)

add_executable(events-test
  tests/Publisher.cpp
)
target_link_libraries(events-test
  events
  gtest_main
)

add_test(NAME events-test COMMAND events-test)
