#ifndef PRODUCT_SERVICE_HPP
#define PRODUCT_SERVICE_HPP

#include <pqxx/pqxx>
#include <optional>
#include <vector>
#include "product/product-repository.hpp"


namespace ProductService {
   //LİSTELEME
    inline std::vector<product> Listproduct(pqxx::connection& conn) {
        return ProductRepository::ListProducts(conn);
    }
    //İD İLE GETİRME
    inline std::optional<product> Getbyidproduct(pqxx::connection &conn, const int productId) {
        return ProductRepository::Getbyidproduct(conn, productId);
    }
    //SİLME
    inline void Deleteproduct(pqxx::connection& conn, const int productId) {
        ProductRepository::DeleteProduct(conn, productId);
    }
    //GÜNCELLEME
    inline void Updateproduct(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        ProductRepository::Updateproduct(conn, name, surname, email, phone);
    }
    //EKLEME
    inline void AddProduct(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        ProductRepository::Addproduct(conn, name, surname, email, phone);
    }

}

#endif // PRODUCT_SERVICE_HPP
