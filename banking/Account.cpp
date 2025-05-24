#include "Account.h"
#include <stdexcept>

Account::Account(int id, int balance)
    : id_(id), balance_(balance), is_locked_(false) {}

int Account::GetBalance() const {
    return balance_;
}

void Account::SetBalance(int balance) {
    balance_ = balance;
}

int Account::GetId() const {
    return id_;
}

void Account::SetId(int id) {
    id_ = id;
}

void Account::Lock() {
    if (is_locked_) throw std::runtime_error("Account already locked");
    is_locked_ = true;
}

void Account::Unlock() {
    is_locked_ = false;
}

void Account::ChangeBalance(int diff) {
    balance_ += diff;
}
