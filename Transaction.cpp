#include "Transaction.h"
#include <iomanip>
#include <sstream>

Transaction::Transaction() : id(0), account(nullptr), type(""), amount(0.0) {
    timestamp = std::time(nullptr);
}

Transaction::Transaction(int id, std::shared_ptr<Account> account, const std::string& type, double amount)
    : id(id), account(account), type(type), amount(amount) {
    timestamp = std::time(nullptr);
}

int Transaction::getId() const { return id; }
std::shared_ptr<Account> Transaction::getAccount() const { return account; }
std::string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }

std::string Transaction::getFormattedTimestamp() const {
    char buffer[26];
#ifdef _WIN32
    ctime_s(buffer, sizeof(buffer), &timestamp);
    std::string res(buffer);
#else
    std::string res(std::ctime(&timestamp));
#endif
    // ctime adds a newline at the end, so we remove it
    if (!res.empty() && res.back() == '\n') {
        res.pop_back();
    }
    return res;
}

void Transaction::setId(int i) { id = i; }
void Transaction::setAccount(std::shared_ptr<Account> a) { account = a; }
void Transaction::setType(const std::string& t) { type = t; }
void Transaction::setAmount(double a) { amount = a; }
