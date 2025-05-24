cmake_minimum_required(VERSION 3.15)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем покрытие (по желанию)
option(COVERAGE "Enable code coverage" ON)
if(COVERAGE)
    message(STATUS "Code coverage enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Добавляем библиотеку
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)

# Подключаем GoogleTest и GoogleMock
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(third-party/gtest)

# Удаляем предупреждения
set_target_properties(gtest PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gtest_main PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gmock PROPERTIES COMPILE_FLAGS "-w")
set_target_properties(gmock_main PROPERTIES COMPILE_FLAGS "-w")

# Включаем тесты
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()

    add_executable(unit_tests
        tests/test_account.cpp
        tests/test_transaction.cpp
    )

    target_include_directories(unit_tests PRIVATE
        third-party/gtest/googlemock/include
        third-party/gtest/googletest/include
    )

    target_link_libraries(unit_tests
        banking
        gtest
        gtest_main
        gmock
        gmock_main
        pthread
    )

    add_test(NAME unit_tests COMMAND unit_tests)
endif()
