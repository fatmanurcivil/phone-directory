#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <utility>

class product {
public:
    product() = default;
    product(const int& id, std::string name, std::string categoryId)
        : id(id), name(std::move(name)),categoryId(std::move(categoryId)),categoryName(std::move(categoryName)) {}


    int id{};
    std::string name;
    std::string categoryId;
    std::string categoryName;

};

#endif
