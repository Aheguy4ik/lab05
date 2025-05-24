cmake_minimum_required(VERSION 3.10)
project(BankingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги, чтобы не превращать warning в error для gtest
add_compile_options(-Wall -Wextra -Wno-error)

add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC ${CMAKE_SOURCE_DIR}/banking)

add_subdirectory(third-party/gtest)

add_executable(unit_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)

# Здесь добавляем путь к банковским хедерам, чтобы тесты их видели
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/banking)

target_link_libraries(unit_tests
    banking
    gtest
    gtest_main
    gmock
    gmock_main
    pthread
)
