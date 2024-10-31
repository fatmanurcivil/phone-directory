#ifndef CONTACTGROUP_FACTORY_HPP
#define CONTACTGROUP_FACTORY_HPP

#include <pqxx/pqxx>
#include "contact-group.hpp"

  namespace ContactGroupFactory {

    // Veritabanı satırını ContactGroup nesnesine dönüştürme
    inline ContactGroup createContactGroupFromRow(const pqxx::row& row) {
        return std::move(ContactGroup{
     row["id"].as<int>(),
     row["group_name"].as<std::string>(),
     row["group_surname"].as<std::string>(),
     row["email"].as<std::string>(),
     row["phone"].as<std::string>()
     });

    }

    // Yeni bir ContactGroup nesnesi oluşturma (ID olmadan ekleme için)
    inline ContactGroup createContactGroup(const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        return ContactGroup{name, surname, email, phone};
    }

    // ID ile birlikte ContactGroup nesnesi oluşturma (Güncelleme için)
    inline ContactGroup createContactGroup(const int id, const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        return ContactGroup{id, name, surname, email, phone};
    }



}


#endif
