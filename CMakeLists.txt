cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для покрытия кода
option(COVERAGE "Enable coverage reporting" ON)
option(BUILD_TESTS "Build tests" ON)

# Флаг покрытия для gcc/clang
if(COVERAGE)
  message(STATUS "Coverage enabled")
  add_compile_options(--coverage)
  link_libraries(--coverage)
endif()

# Подключаем GoogleTest
set(gtest_disable_pthreads ON)
add_subdirectory(third-party/gtest)

# Добавляем библиотеку из исходников
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Тесты
if(BUILD_TESTS)
  enable_testing()
  file(GLOB TEST_SOURCES tests/*.cpp)

  add_executable(test_banking ${TEST_SOURCES})
  target_link_libraries(test_banking banking gtest_main)

  add_test(NAME banking_tests COMMAND test_banking)
endif()
