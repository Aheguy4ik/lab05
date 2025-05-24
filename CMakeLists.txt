cmake_minimum_required(VERSION 3.15)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опционально включаем покрытие кода
option(COVERAGE "Enable coverage reporting" ON)

# Флаги покрытия, если нужно
if(COVERAGE)
    message(STATUS "Code coverage enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Добавляем исходники библиотеки
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Подключаем GoogleTest
# ПЕРЕД add_subdirectory — отключаем Werror (только для GTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(third-party/gtest)

# Удаляем предупреждения для gtest
set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gtest_main PROPERTIES COMPILE_FLAGS "-w")

# Добавляем тесты
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_executable(unit_tests
        tests/test_account.cpp
        tests/test_transaction.cpp
    )

    target_link_libraries(unit_tests
        banking
        gtest
        gtest_main
        pthread
    )

    add_test(NAME unit_tests COMMAND unit_tests)
endif()
