#include "User.h"

User::User() : id(0), name(""), email(""), password("") {}

User::User(int id, const std::string& name, const std::string& email, const std::string& password)
    : id(id), name(name), email(email), password(password) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }
std::string User::getPassword() const { return password; }

void User::setId(int i) { id = i; }
void User::setName(const std::string& n) { name = n; }
void User::setEmail(const std::string& e) { email = e; }
void User::setPassword(const std::string& p) { password = p; }
