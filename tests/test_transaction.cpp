#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Account.h"
#include "Transaction.h"

using namespace testing;

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}

    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
    MOCK_METHOD1(ChangeBalance, void(int));
    MOCK_CONST_METHOD0(GetBalance, int());
    MOCK_CONST_METHOD0(GetId, int());
};

class TestTransaction : public Transaction {
protected:
    void SaveToDataBase([[maybe_unused]] Account& from, [[maybe_unused]] Account& to, [[maybe_unused]] int sum) override {
    // пусто — заглушка
    }
};

TEST(TransactionTest, TransfersMoneyCorrectly) {
    MockAccount from(1, 500);
    MockAccount to(2, 100);
    TestTransaction tx;

    EXPECT_CALL(from, GetId()).WillRepeatedly(Return(1));
    EXPECT_CALL(to, GetId()).WillRepeatedly(Return(2));

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_CALL(from, GetBalance()).WillOnce(Return(500));
    EXPECT_CALL(from, ChangeBalance(-150)).Times(1);
    EXPECT_CALL(to, ChangeBalance(150)).Times(1);

    EXPECT_TRUE(tx.Make(from, to, 150));
}
