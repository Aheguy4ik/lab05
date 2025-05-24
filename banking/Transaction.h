#pragma once

#include "Account.h"

class Transaction {
public:
    virtual ~Transaction() = default;
    bool Make(Account& from, Account& to, int sum);

protected:
    virtual void SaveToDataBase(Account& from, Account& to, int sum);
};
