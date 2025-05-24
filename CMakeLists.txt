cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

enable_testing()

set(Sources
    banking/Account.cpp
    banking/Transaction.cpp
)

set(Headers
    banking/Account.h
    banking/Transaction.h
)

add_library(banking STATIC ${Sources} ${Headers})

target_include_directories(banking PUBLIC ${CMAKE_SOURCE_DIR}/banking)

if(BUILD_TESTS)
    add_subdirectory(third-party/gtest)

    # Глушим предупреждения maybe-uninitialized для googletest
    target_compile_options(gtest PRIVATE -Wno-maybe-uninitialized)
    target_compile_options(gmock PRIVATE -Wno-maybe-uninitialized)
    target_compile_options(gtest_main PRIVATE -Wno-maybe-uninitialized)
    target_compile_options(gmock_main PRIVATE -Wno-maybe-uninitialized)

    add_subdirectory(tests)
endif()
