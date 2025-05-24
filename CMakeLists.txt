cmake_minimum_required(VERSION 3.10)
project(lab05)

option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги покрытия
if(COVERAGE)
  message(STATUS "Building with coverage flags")
  add_compile_options(-fprofile-arcs -ftest-coverage -O0)
  link_libraries(gcov)
endif()

# Твои исходники, например:
add_library(banking
  banking/Account.cpp
  banking/Transaction.cpp
)

if(BUILD_TESTS)
  enable_testing()

  add_executable(unit_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
  )
  target_link_libraries(unit_tests banking gtest gmock pthread)

  add_test(NAME unit_tests COMMAND unit_tests)
endif()
