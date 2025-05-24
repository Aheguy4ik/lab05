cmake_minimum_required(VERSION 3.10)
project(banking)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Отключаем превращение предупреждений в ошибки для gtest (если эта переменная поддерживается)
set(gtest_disable_werror ON CACHE BOOL "" FORCE)

# Подключаем googletest как сабмодуль
add_subdirectory(third-party/gtest)

# Добавляем нашу библиотеку banking из исходников
add_library(banking
    Account.cpp
    Transaction.cpp
)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем тесты
enable_testing()

file(GLOB TEST_SOURCES tests/*.cpp)

add_executable(test_banking ${TEST_SOURCES})

target_link_libraries(test_banking
    banking
    gtest_main
)

add_test(NAME banking_tests COMMAND test_banking)
