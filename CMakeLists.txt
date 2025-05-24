cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции для тестов и покрытия
option(BUILD_TESTS "Build unit tests" ON)
option(COVERAGE "Enable coverage reporting" OFF)

# Добавляем основной код
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Настройка покрытия кода
if(COVERAGE)
    message("Code coverage enabled")
    target_compile_options(banking PRIVATE --coverage)
    target_link_libraries(banking PRIVATE --coverage)
endif()

# Тесты
if(BUILD_TESTS)
    enable_testing()
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(third-party/googletest)

    include_directories(
        third-party/googletest/googletest/include
        third-party/googletest/googlemock/include
    )

    add_executable(unit_tests
        tests/test_account.cpp
        tests/test_transaction.cpp
    )

    target_link_libraries(unit_tests
        banking
        gtest
        gtest_main
        gmock
        gmock_main
    )

    add_test(NAME unit_tests COMMAND unit_tests)
endif()
