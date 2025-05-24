cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage reporting" OFF)

# Включаем покрытие
if(COVERAGE)
  add_compile_options(--coverage)
  link_libraries(gcov)
endif()

# Исходники
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Тесты
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/googletest)

  add_executable(unit_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
  )

  target_link_libraries(unit_tests
    banking
    gtest
    gmock
    gtest_main
    gmock_main
  )

  target_include_directories(unit_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

  add_test(NAME unit_tests COMMAND unit_tests)
endif()
