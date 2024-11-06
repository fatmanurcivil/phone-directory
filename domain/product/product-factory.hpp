#ifndef PRODUCT_FACTORY_HPP
#define PRODUCT_FACTORY_HPP

#include <vector>
#include "product.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ProductFactory {

    inline json createFromResult(const std::vector<product>& products) {
        json result = json::array();

        for (const auto& product : products) {
            result.push_back(
                {
                {"id", product.id},
                {"name", product.name},
                {"surname", product.surname},
                {"phone", product.phone},
                {"email", product.email}
            });
        }

        return result;
    }
}


inline product product::createproductFromRow(const pqxx::row& row) {
    return product(
        row[0].as<int>(),
        row[1].as<std::string>(),
        row[2].as<std::string>(),
        row[3].as<std::string>(),
        row[4].as<std::string>()
    );
}

#endif
