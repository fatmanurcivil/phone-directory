#ifndef PRODUCT_REPOSITORY_H
#define PRODUCT_REPOSITORY_HPP


#include <pqxx/pqxx>
#include <optional>
#include "product/product.hpp"

namespace ProductRepository {

    inline std::vector<product> ListProducts(pqxx::connection& conn) {
        std::vector<product> products;
        pqxx::nontransaction txn(conn);
        const std::string query = "SELECT id, name, surname, email, phone FROM contact_groups";
        const pqxx::result result = txn.exec(query);

        for (const auto& row : result) {
            products.push_back(product::createproductFromRow(row));
        }

        return products;
    }
    // ContactGroup silme
    inline void DeleteProduct(pqxx::connection& conn, int productId) {
        const std::string query = "DELETE FROM contact_groups WHERE id = $1";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, productId);
    }
    inline void Updateproduct(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        const std::string query = "UPDATE contact_groups SET group_name = $1, group_surname = $2, email = $3, phone = $4 WHERE id = $5";  // group_name ve group_surname güncellendi
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, name, surname, email, phone);
    }

    inline std::optional<product> Getbyidproduct(pqxx::connection& conn, int productId) {
        pqxx::nontransaction txn(conn);
        const std::string query = "SELECT id, group_name, group_surname, email, phone FROM contact_groups WHERE id = $1";

        if (const pqxx::result result = txn.exec_params(query, productId); !result.empty()) {
            return product::createproductFromRow(result[0]);
        }
        return std::nullopt;
    }

    inline void Addproduct(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        const std::string query = "INSERT INTO contact_groups (name, surname, email, phone) VALUES ($1, $2, $3, $4)";
        pqxx::work txn(conn);
        txn.exec_params(query, name, surname, email, phone);
    }

}

#endif