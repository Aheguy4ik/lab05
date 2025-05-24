#pragma once

class Account {
public:
    Account(int id, int balance);
    virtual ~Account() = default;

    virtual int GetBalance() const;
    void SetBalance(int balance);

    virtual int GetId() const;
    void SetId(int id);

    virtual void Lock();
    virtual void Unlock();
    virtual void ChangeBalance(int diff);

private:
    int id_;
    int balance_;
    bool is_locked_;
};
