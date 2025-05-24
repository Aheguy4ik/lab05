cmake_minimum_required(VERSION 3.10)
project(BankingApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Указываем исходные файлы для библиотеки
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

# 2. Указываем заголовки, чтобы они были доступны при подключении
target_include_directories(banking PUBLIC ${CMAKE_SOURCE_DIR})

# 3. Добавляем Google Test
add_subdirectory(third-party/gtest)

# 4. Добавляем исполняемый файл для юнит-тестов
add_executable(unit_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)

# 5. Подключаем зависимости к тестам
target_link_libraries(unit_tests
    banking
    gtest
    gtest_main
    gmock
    gmock_main
    pthread
)

# 6. Указываем include директории для тестов
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR})
