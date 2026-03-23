#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <memory>
#include "User.h"

class Account {
private:
    int id;
    std::shared_ptr<User> user;
    double balance;

public:
    Account();
    Account(int id, std::shared_ptr<User> user, double balance = 0.0);

    // Getters
    int getId() const;
    std::shared_ptr<User> getUser() const;
    double getBalance() const;

    // Setters
    void setId(int id);
    void setUser(std::shared_ptr<User> user);
    void setBalance(double balance);
};

#endif // ACCOUNT_H
