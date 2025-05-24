#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "banking/Account.h"
#include "banking/Transaction.h"

using namespace testing;

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}

    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
    MOCK_METHOD(void, ChangeBalance, (int), (override));
    MOCK_METHOD(int, GetBalance, (), (const, override));
};

class TestTransaction : public Transaction {
protected:
    void SaveToDataBase(Account& from, Account& to, int sum) override {
        // мокать не будем, но можем логировать
    }
};

TEST(TransactionTest, TransfersMoneyCorrectly) {
    MockAccount from(1, 500);
    MockAccount to(2, 100);
    TestTransaction tx;

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_CALL(from, GetBalance()).WillOnce(Return(500));
    EXPECT_CALL(from, ChangeBalance(-150)).Times(1);
    EXPECT_CALL(to, ChangeBalance(150)).Times(1);

    EXPECT_TRUE(tx.Make(from, to, 150));
}
