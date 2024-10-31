#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <utility>

class Contact {
public:

    Contact() = default;

    Contact(const int id, std::string name, std::string surname, std::string email, std::string phone)
        : id(id), name(std::move(name)), surname(std::move(surname)), email(std::move(email)), phone(std::move(phone)) {}

    int id{};
    std::string name;
    std::string surname;
    std::string email;
    std::string phone;
};

#endif //CONTACT_HPP
