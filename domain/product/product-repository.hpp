#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_HPP

#include <pqxx/pqxx>
#include "product/product.hpp"

namespace ProductRepository {

    inline void DeleteProduct(pqxx::connection& conn, int id) {
        const std::string query = "DELETE FROM product WHERE id = $1";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, id);
    }

    inline void updateProduct(pqxx::connection& conn, int id, const std::string& name, int categoryId, const std::string& categoryName) {
        const std::string query = "UPDATE product SET name = $1, categoryId = $2, categoryName = $3 WHERE id = $4";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, name, categoryId, categoryName, id);
    }

    inline void Addproduct(pqxx::connection& conn, const std::string& name, int categoryId, const std::string& categoryName) {
        const std::string query = "INSERT INTO product (name, categoryId, categoryName) VALUES ($1, $2, $3)";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, name, categoryId, categoryName);
    }

    inline std::vector<std::tuple<int, std::string, int, std::string>> ListProducts(pqxx::connection& conn) {
        const std::string query = "SELECT id, name, categoryId, categoryName FROM product";
        pqxx::nontransaction txn(conn);
        const pqxx::result result = txn.exec(query);

        std::vector<std::tuple<int, std::string, int, std::string>> products;
        for (const auto& row : result) {
            products.emplace_back(row[0].as<int>(), row[1].as<std::string>(), row[2].as<int>(), row[3].as<std::string>());
        }

        return products;
    }

}

#endif
