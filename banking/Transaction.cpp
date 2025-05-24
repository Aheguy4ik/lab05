#include "Transaction.h"

bool Transaction::Make(Account& from, Account& to, int sum) {
    if (from.GetId() == to.GetId() || sum <= 0 || from.GetBalance() < sum) {
        return false;
    }

    from.Lock();
    to.Lock();

    from.ChangeBalance(-sum);
    to.ChangeBalance(sum);

    SaveToDataBase(from, to, sum);

    from.Unlock();
    to.Unlock();

    return true;
}

void Transaction::SaveToDataBase(Account&, Account&, int) {
    // Пусто — или логика записи в БД
}
