#include <gtest/gtest.h>
#include "banking/Account.h"

TEST(AccountTest, InitialBalanceCorrect) {
    Account acc(1, 100);
    EXPECT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, ChangeBalanceThrowsIfNotLocked) {
    Account acc(1, 100);
    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
}

TEST(AccountTest, ChangeBalanceWhenLocked) {
    Account acc(1, 100);
    acc.Lock();
    acc.ChangeBalance(50);
    EXPECT_EQ(acc.GetBalance(), 150);
}

TEST(AccountTest, DoubleLockThrows) {
    Account acc(1, 100);
    acc.Lock();
    EXPECT_THROW(acc.Lock(), std::runtime_error);
}
