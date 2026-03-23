#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    int id;
    std::string name;
    std::string email;
    std::string password;

public:
    User();
    User(int id, const std::string& name, const std::string& email, const std::string& password);

    // Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
};

#endif // USER_H
