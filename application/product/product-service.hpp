#ifndef PRODUCT_SERVICE_H
#define PRODUCT_SERVICE_H

#include <string>
#include <pqxx/pqxx>
#include "../../domain/product/product-service.hpp"

namespace ProductContactService {
    inline void AddProduct(pqxx::connection &conn, const std::string& categoryId, int name, const std::string &categoryName) {
        ProductRepository::Addproduct(conn, categoryId, name, categoryName);
    }
    inline void DeleteProduct(pqxx::connection &conn, const int id) {
        ProductRepository::DeleteProduct(conn, id);
    }
    inline std::vector<std::tuple<int, std::string, int, std::string>> ListProducts(pqxx::connection &conn) {
        return ProductRepository::ListProducts(conn);
    }
    inline void UpdateProduct(pqxx::connection &conn, const int id, const std::string &name, const int categoryId, const std::string &categoryName) {
        ProductRepository::updateProduct(conn, id, name, categoryId, categoryName);
    }

}
#endif
