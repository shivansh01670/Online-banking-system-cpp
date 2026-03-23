#include "BankService.h"
#include <iostream>
#include <algorithm>

BankService::BankService() 
    : loggedInUser(nullptr), nextUserId(1), nextAccountId(1), nextTransactionId(1) {}

bool BankService::isLoggedIn() const {
    return loggedInUser != nullptr;
}

std::shared_ptr<Account> BankService::getLoggedInUserAccount() {
    if (!loggedInUser) return nullptr;
    
    for (const auto& pair : accountsById) {
        if (pair.second->getUser() && pair.second->getUser()->getId() == loggedInUser->getId()) {
            return pair.second;
        }
    }
    return nullptr;
}

void BankService::registerUser(const std::string& name, const std::string& email, const std::string& password) {
    if (usersByEmail.find(email) != usersByEmail.end()) {
        std::cout << "❌ User with this email already exists.\n";
        return;
    }
    
    auto user = std::make_shared<User>(nextUserId++, name, email, password);
    usersById[user->getId()] = user;
    usersByEmail[user->getEmail()] = user;
    
    std::cout << "✅ User registered successfully!\n";
}

void BankService::login(const std::string& email, const std::string& password) {
    if (usersByEmail.find(email) != usersByEmail.end()) {
        auto user = usersByEmail[email];
        if (user->getPassword() == password) {
            loggedInUser = user;
            std::cout << "✅ Login successful. Welcome " << loggedInUser->getName() << "\n";
            return;
        }
    }
    std::cout << "❌ Invalid credentials.\n";
}

void BankService::logout() {
    loggedInUser = nullptr;
    std::cout << "✅ Logged out successfully.\n";
}

void BankService::createAccount() {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }
    
    if (getLoggedInUserAccount() != nullptr) {
        std::cout << "❌ You already have an account.\n";
        return;
    }

    auto account = std::make_shared<Account>(nextAccountId++, loggedInUser, 0.0);
    accountsById[account->getId()] = account;
    
    std::cout << "✅ Account created. Account ID: " << account->getId() << "\n";
}

void BankService::deposit(double amount) {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }
    if (amount <= 0) {
        std::cout << "❌ Invalid amount.\n";
        return;
    }

    auto account = getLoggedInUserAccount();
    if (account) {
        account->setBalance(account->getBalance() + amount);
        
        auto txn = std::make_shared<Transaction>(nextTransactionId++, account, "DEPOSIT", amount);
        transactions.push_back(txn);
        
        std::cout << "✅ Deposited " << amount << ". New balance: " << account->getBalance() << "\n";
    } else {
        std::cout << "❌ No account found.\n";
    }
}

void BankService::withdraw(double amount) {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }
    if (amount <= 0) {
        std::cout << "❌ Invalid amount.\n";
        return;
    }

    auto account = getLoggedInUserAccount();
    if (account && account->getBalance() >= amount) {
        account->setBalance(account->getBalance() - amount);
        
        auto txn = std::make_shared<Transaction>(nextTransactionId++, account, "WITHDRAW", amount);
        transactions.push_back(txn);
        
        std::cout << "✅ Withdrawn " << amount << ". New balance: " << account->getBalance() << "\n";
    } else {
        std::cout << "❌ Insufficient balance or no account found.\n";
    }
}

void BankService::showBalance() {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }

    auto account = getLoggedInUserAccount();
    if (account) {
        std::cout << "💰 Current balance: " << account->getBalance() << "\n";
    } else {
        std::cout << "❌ No account found.\n";
    }
}

void BankService::transfer(int toAccountId, double amount) {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }
    if (amount <= 0) {
        std::cout << "❌ Invalid amount.\n";
        return;
    }

    auto sender = getLoggedInUserAccount();
    if (!sender) {
        std::cout << "❌ You don't have an account.\n";
        return;
    }
    
    if (accountsById.find(toAccountId) == accountsById.end()) {
        std::cout << "❌ Recipient account not found.\n";
        return;
    }
    
    auto receiver = accountsById[toAccountId];

    if (sender->getBalance() >= amount) {
        sender->setBalance(sender->getBalance() - amount);
        receiver->setBalance(receiver->getBalance() + amount);

        auto txnOut = std::make_shared<Transaction>(nextTransactionId++, sender, "TRANSFER_OUT", amount);
        auto txnIn = std::make_shared<Transaction>(nextTransactionId++, receiver, "TRANSFER_IN", amount);
        transactions.push_back(txnOut);
        transactions.push_back(txnIn);

        std::cout << "✅ Transferred " << amount << " to Account " << toAccountId << "\n";
    } else {
        std::cout << "❌ Transfer failed. Check balance.\n";
    }
}

void BankService::showTransactions() {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }

    auto account = getLoggedInUserAccount();
    if (account) {
        bool found = false;
        std::cout << "📜 Transaction History:\n";
        for (const auto& txn : transactions) {
            if (txn->getAccount() && txn->getAccount()->getId() == account->getId()) {
                std::cout << txn->getId() << " | " << txn->getType() << " | " << txn->getAmount() << " | " << txn->getFormattedTimestamp() << "\n";
                found = true;
            }
        }
        if (!found) {
            std::cout << "❌ No transactions found.\n";
        }
    } else {
        std::cout << "❌ No account found.\n";
    }
}

void BankService::deleteAccount(int accountId) {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }

    if (accountsById.find(accountId) != accountsById.end()) {
        auto account = accountsById[accountId];
        if (account->getUser() && account->getUser()->getId() == loggedInUser->getId()) {
            
            // Remove transactions associated with this account to avoid dangling resources
            transactions.erase(
                std::remove_if(transactions.begin(), transactions.end(),
                               [accountId](std::shared_ptr<Transaction> t) {
                                   return t->getAccount() && t->getAccount()->getId() == accountId;
                               }),
                transactions.end());
                
            accountsById.erase(accountId);
            std::cout << "✅ Account deleted successfully.\n";
        } else {
            std::cout << "❌ Unauthorized.\n";
        }
    } else {
        std::cout << "❌ Account not found.\n";
    }
}

void BankService::generateBankStatement(int accountId) {
    if (!isLoggedIn()) {
        std::cout << "⚠️ Please login first.\n";
        return;
    }

    if (accountsById.find(accountId) != accountsById.end()) {
        auto account = accountsById[accountId];
        if (account->getUser() && account->getUser()->getId() == loggedInUser->getId()) {
            std::cout << "========== Bank Statement ==========\n";
            std::cout << "Account ID: " << account->getId() << "\n";
            std::cout << "User: " << loggedInUser->getName() << "\n";
            std::cout << "Balance: " << account->getBalance() << "\n";

            for (const auto& txn : transactions) {
                if (txn->getAccount() && txn->getAccount()->getId() == accountId) {
                    std::cout << txn->getFormattedTimestamp() << " | " << txn->getType() << " | " << txn->getAmount() << "\n";
                }
            }
            std::cout << "====================================\n";
        } else {
            std::cout << "❌ Unauthorized.\n";
        }
    } else {
         std::cout << "❌ Account not found.\n";
    }
}
