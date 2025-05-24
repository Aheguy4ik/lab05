#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"

using ::testing::Return;
using ::testing::_;

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}

    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

class TestTransaction : public Transaction {
public:
    MOCK_METHOD(void, SaveToDataBase, (Account&, Account&, int), (override));
};

TEST(TransactionTest, MakeFailsOnSameAccount) {
    TestTransaction tx;
    MockAccount acc(1, 100);
    EXPECT_THROW(tx.Make(acc, acc, 100), std::logic_error);
}

TEST(TransactionTest, MakeFailsOnSmallSum) {
    TestTransaction tx;
    MockAccount acc1(1, 100), acc2(2, 100);
    EXPECT_THROW(tx.Make(acc1, acc2, 50), std::logic_error);
}

TEST(TransactionTest, MakeSuccess) {
    TestTransaction tx;
    tx.set_fee(1);
    MockAccount from(1, 500), to(2, 100);

    EXPECT_CALL(from, Lock());
    EXPECT_CALL(to, Lock());
    EXPECT_CALL(from, Unlock());
    EXPECT_CALL(to, Unlock());

    EXPECT_CALL(to, ChangeBalance(150));
    EXPECT_CALL(to, GetBalance()).WillRepeatedly(Return(151));
    EXPECT_CALL(to, ChangeBalance(-151));

    EXPECT_CALL(from, GetBalance()).WillRepeatedly(Return(500));
    EXPECT_CALL(from, ChangeBalance(-151));
    EXPECT_CALL(tx, SaveToDataBase(_, _, 150));

    EXPECT_TRUE(tx.Make(from, to, 150));
}

