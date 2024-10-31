#ifndef CONTACTGROUP_HPP
#define CONTACTGROUP_HPP

#include <string>
#include <nlohmann/json.hpp>

class ContactGroup {
public:
    int id{};
    std::string groupName;
    std::string groupSurname;
    std::string email;
    std::string phone;

    ContactGroup() = default;



    // ID olmadan kullanılabilecek construct or
    ContactGroup(std::string groupName, std::string groupSurname, std::string email, std::string phone)
        : groupName(std::move(groupName)), groupSurname(std::move(groupSurname)), email(std::move(email)), phone(std::move(phone)) {}

    // ID ile birlikte kullanılabilecek constructor
    ContactGroup(const int id, std::string groupName, std::string groupSurname, std::string email, std::string phone)
        : id(id), groupName(std::move(groupName)), groupSurname(std::move(groupSurname)), email(std::move(email)), phone(std::move(phone)) {}

};

#endif
