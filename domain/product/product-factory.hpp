#ifndef PRODUCT_FACTORY_HPP
#define PRODUCT_FACTORY_HPP

#include <vector>
#include "product.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <pqxx/pqxx>

using json = nlohmann::json;

namespace ProductFactory {


    inline std::vector<product> createproductFromRow(const pqxx::result& rows) {
        std::vector<product> productList;

        for (const auto& row : rows) {
            product product;
            product.id = row[0].as<int>();
            product.name = row[1].as<std::string>();
            product.categoryId = row[2].as<std::string>();
            product.categoryName = row[3].as<std::string>();
            productList.push_back(product);
        }

        return productList;
    }

}

#endif
