cmake_minimum_required(VERSION 3.10)

project(lab05)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Отключаем превращение warning в error (иначе gtest не соберётся)
add_compile_options(-Wall -Wextra -Wno-error)

# Либа banking
add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

# Указываем пути для инклюдов библиотеки banking
target_include_directories(banking PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/banking
)

# Настройки для GTest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON)
set(BUILD_GTEST ON)
set(INSTALL_GTEST OFF)

# Подключаем gtest как сабдиректорию
add_subdirectory(third-party/gtest)

# Исполняемый файл для юнит-тестов
add_executable(unit_tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)

# Включаем пути для тестов (чтобы находились хедеры banking и корень)
target_include_directories(unit_tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/banking
)

# Линкуем тесты с нужными библиотеками
target_link_libraries(unit_tests
    banking
    gtest
    gtest_main
    gmock
    gmock_main
    pthread
)
