#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <memory>
#include <ctime>
#include "Account.h"

class Transaction {
private:
    int id;
    std::shared_ptr<Account> account;
    std::string type; // DEPOSIT, WITHDRAW, TRANSFER_IN, TRANSFER_OUT
    double amount;
    std::time_t timestamp;

public:
    Transaction();
    Transaction(int id, std::shared_ptr<Account> account, const std::string& type, double amount);

    // Getters
    int getId() const;
    std::shared_ptr<Account> getAccount() const;
    std::string getType() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    std::string getFormattedTimestamp() const;

    // Setters
    void setId(int id);
    void setAccount(std::shared_ptr<Account> account);
    void setType(const std::string& type);
    void setAmount(double amount);
};

#endif // TRANSACTION_H
