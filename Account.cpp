#include "Account.h"

Account::Account() : id(0), user(nullptr), balance(0.0) {}

Account::Account(int id, std::shared_ptr<User> user, double balance)
    : id(id), user(user), balance(balance) {}

int Account::getId() const { return id; }
std::shared_ptr<User> Account::getUser() const { return user; }
double Account::getBalance() const { return balance; }

void Account::setId(int i) { id = i; }
void Account::setUser(std::shared_ptr<User> u) { user = u; }
void Account::setBalance(double b) { balance = b; }
