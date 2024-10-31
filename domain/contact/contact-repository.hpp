#ifndef CONTACT_REPOSITORY_HPP
#define CONTACT_REPOSITORY_HPP

#include "contact.hpp"
#include "contact-factory.hpp"
#include <pqxx/pqxx>
#include <optional>

namespace ContactRepository {

    // Yeni bir contact ekleme
    inline void addContact(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& phone, const std::string& email) {
        const std::string query = "INSERT INTO phonebook (name, surname, email, phone_number) VALUES ($1, $2, $3, $4)";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query,name, surname, email, phone);

    }
    inline std::vector<Contact> listContacts(pqxx::connection& conn, const std::optional<int>& id = std::nullopt,
                                           const std::optional<int>& page = std::nullopt,
                                           const std::optional<int>& pageSize = std::nullopt) {
        std::vector<Contact> contacts;
        pqxx::nontransaction txn(conn);
        std::string query;

        if (id.has_value()) {
            query = "SELECT id, name, surname, email, phone_number FROM phonebook WHERE id = $1";
        } else {
            query = "SELECT id, name, surname, email, phone_number FROM phonebook";
            if (page.has_value() && pageSize.has_value()) {
                query += " LIMIT $1 OFFSET $2";
            }
        }
        pqxx::result result;

        if (id.has_value()) {
            result = txn.exec_params(query, id.value());
        } else if (page.has_value() && pageSize.has_value()) {
            result = txn.exec_params(query, pageSize.value(), (page.value() - 1) * pageSize.value());
        } else {
            result = txn.exec(query);
        }

        for (const auto& row : result) {
            contacts.push_back(ContactFactory::createContactFromRow(row));
        }

        return contacts;
    }

    // Contact silme
    inline void deleteContact(pqxx::connection& conn, const int id) {
        if (id == -1) {
            throw std::invalid_argument("Invalid contact ID");
        }
        const std::string query = "DELETE FROM phonebook WHERE id = $1";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, id);

    }

    // Contact güncelleme
    inline void updateContact(pqxx::connection& conn, const Contact& contact) {
        const std::string query = "UPDATE phonebook SET name = $1, surname = $2, email = $3, phone_number = $4 WHERE id = $5";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, contact.name, contact.surname, contact.email, contact.phone, contact.id);

    }

} // namespace ContactRepository

#endif // CONTACT_REPOSITORY_HPP

