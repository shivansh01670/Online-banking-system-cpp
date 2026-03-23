#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "User.h"
#include "Account.h"
#include "Transaction.h"

class BankService {
private:
    std::unordered_map<int, std::shared_ptr<User>> usersById;
    std::unordered_map<std::string, std::shared_ptr<User>> usersByEmail;
    
    std::unordered_map<int, std::shared_ptr<Account>> accountsById;
    
    std::vector<std::shared_ptr<Transaction>> transactions;

    std::shared_ptr<User> loggedInUser;

    int nextUserId;
    int nextAccountId;
    int nextTransactionId;

    // Helper
    std::shared_ptr<Account> getLoggedInUserAccount();

public:
    BankService();

    void registerUser(const std::string& name, const std::string& email, const std::string& password);
    void login(const std::string& email, const std::string& password);
    void logout();
    
    void createAccount();
    void deposit(double amount);
    void withdraw(double amount);
    void showBalance();
    
    void transfer(int toAccountId, double amount);
    void showTransactions();
    void deleteAccount(int accountId);
    void generateBankStatement(int accountId);
    
    bool isLoggedIn() const;
};

#endif // BANKSERVICE_H
