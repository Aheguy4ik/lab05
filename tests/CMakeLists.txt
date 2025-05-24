add_executable(my_test
    test_account.cpp
    test_transaction.cpp
)

target_include_directories(my_test PRIVATE ${CMAKE_SOURCE_DIR}/banking)

target_link_libraries(my_test
    gtest_main
    gmock_main
    banking
)

# Добавляем тест в CTest
add_test(NAME my_test COMMAND my_test)
