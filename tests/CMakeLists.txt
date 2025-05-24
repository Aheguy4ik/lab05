file(GLOB TEST_SOURCES "*.cpp")

add_executable(check ${TEST_SOURCES})

target_link_libraries(check
  banking
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(check)
