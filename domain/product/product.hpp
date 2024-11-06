#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <utility>
#include <pqxx/pqxx>

class product {
public:
    product() = default;

    product(const int id, std::string name, std::string surname, std::string email, std::string phone)
        : id(id), name(std::move(name)), surname(std::move(surname)), email(std::move(email)), phone(std::move(phone)) {}

    static product createproductFromRow(const pqxx::row& row);

    int id{};
    std::string name;
    std::string surname;
    std::string email;
    std::string phone;
};

#endif
