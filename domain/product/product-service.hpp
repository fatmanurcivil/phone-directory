#ifndef PRODUCT_SERVICE_HPP
#define PRODUCT_SERVICE_HPP

#include <pqxx/pqxx>
#include <vector>
#include <string>
#include "product/product-repository.hpp"

namespace ProductService {

    inline void DeleteProduct(pqxx::connection& conn, const int id) {
        ProductRepository::DeleteProduct(conn, id);
    }

    inline void UpdateProduct(pqxx::connection& conn, const int id, const std::string& name, const int categoryId, const std::string& categoryName) {
        ProductRepository::updateProduct(conn, id, name, categoryId, categoryName);
    }

    inline void AddProduct(pqxx::connection& conn, const std::string& name, const int categoryId, const std::string& categoryName) {
        ProductRepository::Addproduct(conn, name, categoryId, categoryName);
    }

    inline std::vector<std::tuple<int, std::string, int, std::string>> ListProducts(pqxx::connection& conn) {
        return ProductRepository::ListProducts(conn);
    }

}

#endif // PRODUCT_SERVICE_HPP
