#ifndef CONTACT_SERVICE_HPP
#define CONTACT_SERVICE_HPP

#include <vector>
#include "contact-repository.hpp"
#include <pqxx/pqxx>

namespace ContactService {

    inline void updateContact(pqxx::connection &conn, const Contact& contact) {
        ContactRepository::updateContact(conn, contact);
    }
    // Yeni bir Contact ekleme
    inline void addContact(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& phone, const std::string& email) {
        ContactRepository::addContact(conn, name,surname, phone, email);
    }
    // Contact silme
    inline void deleteContact(pqxx::connection &conn, const int contactId) {
        ContactRepository::deleteContact(conn, contactId);
    }
    // Contactları listeleme
    inline std::vector<Contact> listContacts(pqxx::connection &conn, const std::optional<int>& id = std::nullopt,
                                           int page = 1, int pageSize = 5) {
        return ContactRepository::listContacts(conn, id);
    }


}

#endif // CONTACT_SERVICE_HPP
