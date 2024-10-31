#ifndef CONTACT_FACTORY_HPP
#define CONTACT_FACTORY_HPP

#include "contact.hpp"
#include <nlohmann/json.hpp>
#include <pqxx/pqxx>

using json = nlohmann::json;

namespace ContactFactory {

    // Veritabanı satırından bir Contact nesnesi oluşturur
    inline Contact createContactFromRow(const pqxx::row& row) {
        return Contact{
            row.at("id").as<int>(),
            row.at("name").as<std::string>(),
            row.at("surname").as<std::string>(),
            row.at("email").as<std::string>(),
            row.at("phone_number").as<std::string>()
        };
    }

    // Yeni bir Contact nesnesi oluşturur (veritabanına eklemek için)
    inline Contact createContactForDb(const std::string& name, const std::string& surname,
                                       const std::string& phone, const std::string& email) {
        return Contact{0, name, surname, email, phone}; // ID 0 olarak ayarlanır, veritabanında otomatik artar
    }

    // JSON'dan Contact nesnesi oluşturur
    inline Contact createContactFromJson(const json& data) {
        return Contact{
            0, // ID 0 olarak ayarlanır, veritabanında otomatik artar
            data.at("name").get<std::string>(),
            data.at("surname").get<std::string>(),
            data.at("email").get<std::string>(),
            data.at("phone").get<std::string>()
        };
    }

    // Contact nesnelerini JSON formatında döndürür
    inline json contactsToJson(const std::vector<Contact>& contacts) {
        json result = json::array(); // JSON dizisi oluştur

        for (const auto& contact : contacts) {
            result.push_back({
                {"id", contact.id},
                {"name", contact.name},
                {"surname", contact.surname},
            });
        }


        return result; // JSON dizisini döndür
    }

} // namespace ContactFactory

#endif // CONTACT_FACTORY_HPP
