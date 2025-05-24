cmake_minimum_required(VERSION 3.15)
project(lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции для покрытия кода
option(BUILD_TESTS "Build tests" ON)
option(COVERAGE "Enable coverage reporting" OFF)

if(COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Подключаем googletest (предполагаем, что он в third-party/googletest)
add_subdirectory(third-party/googletest)

# Собираем библиотеку banking из исходников
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC banking)

if(BUILD_TESTS)
    enable_testing()

    add_executable(unit_tests
        tests/test_account.cpp
        tests/test_transaction.cpp
    )

    target_link_libraries(unit_tests PRIVATE banking gtest gtest_main)

    add_test(NAME unit_tests COMMAND unit_tests)
endif()
