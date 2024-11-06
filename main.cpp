#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <crow.h>
#include <nlohmann/json.hpp>
#include "application/contact/contact-service.hpp"
#include "application/product/product-service.hpp"
#include "product-factory.hpp"

using json = nlohmann::json;

int main() {
    try {
        pqxx::connection conn("dbname=postgres user=postgres password=postgres host=127.0.0.1 port=5432");
        crow::SimpleApp app;

        // Ekleme isteği
        CROW_ROUTE(app, "/add_contact").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                const auto data = json::parse(req.body);
                ApplicationContactService::addContact(conn,
                    data.at("name").get<std::string>(),
                    data.at("surname").get<std::string>(),
                    data.at("phone").get<std::string>(),
                    data.at("email").get<std::string>()
                );

                return crow::response{"application/json", json{{"message", "Contact added successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Invalid user data: " + std::string(e.what())}}.dump()};
            }
        });

        // Güncelleme isteği
        CROW_ROUTE(app, "/update_contact").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                const auto data = json::parse(req.body);
                const Contact contact = {
                    data.at("id").get<int>(),
                    data.at("name").get<std::string>(),
                    data.at("surname").get<std::string>(),
                    data.at("email").get<std::string>(),
                    data.at("phone").get<std::string>()
                };

                // Güncellemeyi yap
                ApplicationContactService::updateContact(conn, contact);

                return crow::response{"application/json", json{{"message", "Contact updated successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Update failed: " + std::string(e.what())}}.dump()};
            }
        });

        // Listeleme isteği
        CROW_ROUTE(app, "/list_contacts").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                const auto contacts = ApplicationContactService::listContacts(conn);
                const json result = ContactFactory::contactsToJson(contacts);
                return crow::response{"application/json", result.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Failed to retrieve contacts: " + std::string(e.what())}}.dump()};
            }
        });

        // Silme isteği
        CROW_ROUTE(app, "/delete_contact").methods(crow::HTTPMethod::DELETE)([&conn](const crow::request& req) {
            try {
                const auto data = json::parse(req.body);
                const int id = data.at("id").get<int>();
                ApplicationContactService::deleteContact(conn, id);

                return crow::response{"application/json", json{{"message", "Contact deleted successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Contact not found: " + std::string(e.what())}}.dump()};
            }
        });

        /////////////////// CONTACT GROUP ///////////////

        CROW_ROUTE(app, "/list_contact_groups").methods(crow::HTTPMethod::GET)([&conn]() {
            try {
                const auto getgroups = ApplicationContactService::getContactGroups(conn);
                std::vector<nlohmann::json> jsonGroups;

                for (const auto& group : getgroups) {
                    jsonGroups.push_back({{"id", group.id}, {"name", group.groupName}, {"surname", group.groupSurname}});
                }
                return crow::response{"application/json", nlohmann::json(jsonGroups).dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", nlohmann::json{{"error", e.what()}}.dump()};
            }
        });

        CROW_ROUTE(app, "/delete_contact_group").methods(crow::HTTPMethod::DELETE)([&conn](const crow::request& req) {
            try {
                auto data = nlohmann::json::parse(req.body);
                const int id = data["id"].get<int>();

                ApplicationContactService::deleteContactGroup(conn, id);
                return crow::response{"application/json", nlohmann::json{{"message", "Contact group deleted"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", nlohmann::json{{"error", e.what()}}.dump()};
            }
        });

        CROW_ROUTE(app, "/update_contact_group").methods(crow::HTTPMethod::PUT)([&conn](const crow::request& req) {
            try {
                auto data = nlohmann::json::parse(req.body);
                const int id = data["id"].get<int>();
                const std::string name = data["name"].get<std::string>();
                const std::string surname = data.value("surname", "");
                const std::string email = data.value("email", "");
                const std::string phone = data.value("phone", "");

                ApplicationContactService::updateContactGroup(conn, id, name, surname, email, phone);

                return crow::response{"application/json", nlohmann::json{{"message", "Contact group updated"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", nlohmann::json{{"error", e.what()}}.dump()};
            }
        });

        CROW_ROUTE(app, "/add_contact_group").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                auto data = nlohmann::json::parse(req.body);
                const std::string name = data["name"].get<std::string>();
                const std::string surname = data["surname"].get<std::string>();
                const std::string phone = data["phone"].get<std::string>();
                const std::string email = data["email"].get<std::string>();

                ApplicationContactService::addContactGroup(conn, name, surname, email, phone);
                return crow::response{"application/json", nlohmann::json{{"message", "Contact group added successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", nlohmann::json{{"error", e.what()}}.dump()};
            }
        });

        CROW_ROUTE(app, "/get_contact_group_by_id").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                const auto json = crow::json::load(req.body);

                if (!json || !json["groupId"]) {
                    return crow::response(400, R"({"error": "Group ID not provided"})");
                }
                const int groupId = static_cast<int>(json["groupId"].i());
                const std::optional<ContactGroup> optionalGroup = ApplicationContactService::getContactGroupById(conn, groupId);

                if (!optionalGroup.has_value()) {
                    return crow::response(404, R"({"error": "Contact Group not found"})");
                }

                const ContactGroup& group = optionalGroup.value();

                if (group.groupName.empty() || group.groupSurname.empty() || group.email.empty() || group.phone.empty()) {
                    return crow::response(400, R"({"error": "Contact Group has missing fields"})");
                }

                const nlohmann::json jsonGroup = {
                    {"id", group.id},
                    {"name", group.groupName},
                    {"surname", group.groupSurname},
                    {"phone", group.phone},
                    {"email", group.email}
                };

                return crow::response{"application/json", jsonGroup.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", nlohmann::json{{"error", e.what()}}.dump()};
            }
        });

        /////////////////////////////PRODUCT//////////////////////////////////

        // Product Ekleme isteği
        CROW_ROUTE(app, "/addProduct").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                auto data = json::parse(req.body);
                const std::string name = data["name"].get<std::string>();
                const std::string surname = data["surname"].get<std::string>();
                const std::string email = data["email"].get<std::string>();
                const std::string phone = data["phone"].get<std::string>();

                ProductService::AddProduct(conn, name, surname, email, phone);

                return crow::response{"application/json", json{{"message", "Product added successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Failed to add product: " + std::string(e.what())}}.dump()};
            }
        });
        // Product Güncelleme isteği
        CROW_ROUTE(app, "/update_product").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                auto data = nlohmann::json::parse(req.body);
                const std::string name = data["name"].get<std::string>();
                const std::string surname = data.value("surname", "");
                const std::string email = data.value("email", "");
                const std::string phone = data.value("phone", "");

                ProductService::Updateproduct(conn, name,surname,email,phone);

                return crow::response{"application/json", json{{"message", "Product updated successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Update failed: " + std::string(e.what())}}.dump()};
            }
        });

        // Product Listeleme isteği
        CROW_ROUTE(app, "/Listproduct").methods(crow::HTTPMethod::GET)([&conn]() {
           try {
               const auto products = ProductService::Listproduct(conn);
               const json result = ProductFactory::createFromResult(products);
               return crow::response{"application/json", result.dump()};
           } catch (const std::exception& e) {
               return crow::response{"application/json", json{{"error", "Failed to retrieve products: " + std::string(e.what())}}.dump()};
           }
       });

        // Product Silme isteği
        CROW_ROUTE(app, "/Deleteproduct").methods(crow::HTTPMethod::DELETE)([&conn](const crow::request& req) {
            try {
                const auto data = json::parse(req.body);
                const int id = data.at("id").get<int>();
                ProductService::Deleteproduct(conn, id);
                return crow::response{"application/json", json{{"message", "Product deleted successfully"}}.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", "Product not found: " + std::string(e.what())}}.dump()};
            }
        });

        // Product ID ile Getirme isteği
        CROW_ROUTE(app, "/Getbyidproduct").methods(crow::HTTPMethod::POST)([&conn](const crow::request& req) {
            try {
                const auto json = crow::json::load(req.body);

                if (!json || !json["productId"]) {
                    return crow::response(400, R"({"error": "Product ID not provided"})");
                }
                const int productId = static_cast<int>(json["productId"].i());
                const std::optional optionalProduct = ProductService::Getbyidproduct(conn, productId);

                if (!optionalProduct.has_value()) {
                    return crow::response(404, R"({"error": "Product not found"})");
                }

                const product& product = optionalProduct.value();
                const nlohmann::json jsonproduct = {
                       {"id", product.id},
                       {"name", product.name},
                       {"surname", product.surname},
                       {"phone", product.phone},
                       {"email", product.email}
                   };
                return crow::response{"application/json", jsonproduct.dump()};
            } catch (const std::exception& e) {
                return crow::response{"application/json", json{{"error", e.what()}}.dump()};
            }
        });
        app.port(18080).multithreaded().run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

}
