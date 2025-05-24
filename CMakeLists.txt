cmake_minimum_required(VERSION 3.10)
project(BankingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Отключаем Werror, иначе GTest может не собраться
add_compile_options(-Wall -Wextra -Wno-error)

# Либа banking
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)
target_include_directories(banking PUBLIC ${CMAKE_SOURCE_DIR})

# Добавляем GTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON)
set(BUILD_GTEST ON)
set(INSTALL_GTEST OFF)

# --- КЛЮЧЕВАЯ СТРОКА ---
add_subdirectory(third-party/gtest)

# Тесты
add_executable(unit_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(unit_tests
    banking
    gtest
    gtest_main
    gmock
    gmock_main
    pthread
)
