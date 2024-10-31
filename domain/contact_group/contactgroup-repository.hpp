#ifndef CONTACTGROUP_REPOSITORY_HPP
#define CONTACTGROUP_REPOSITORY_HPP

#include "contact-group.hpp"
#include "contactgroup-factory.hpp"
#include <pqxx/pqxx>
#include <optional>

namespace ContactGroupRepository {

    // Tüm ContactGroup'ları listeleme
    inline std::vector<ContactGroup> listContactGroups(pqxx::connection& conn) {
        std::vector<ContactGroup> groups;
        pqxx::nontransaction txn(conn);
        const std::string query = "SELECT id, group_name, group_surname, email, phone FROM contact_groups";
        const pqxx::result result = txn.exec(query);

        for (const auto& row : result) {
            groups.push_back(ContactGroupFactory::createContactGroupFromRow(row));
        }

        return groups;
    }

    // ContactGroup silme
    inline void deleteContactGroup(pqxx::connection& conn, int groupId) {
        const std::string query = "DELETE FROM contact_groups WHERE id = $1";
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, groupId);
    }
    inline void updateContactGroup(pqxx::connection& conn, int groupId, const std::string& groupName, const std::string& groupSurname, const std::string& email, const std::string& phone) {
        const std::string query = "UPDATE contact_groups SET group_name = $1, group_surname = $2, email = $3, phone = $4 WHERE id = $5";  // group_name ve group_surname güncellendi
        pqxx::nontransaction txn(conn);
        txn.exec_params(query, groupName,groupSurname, email, phone,groupId);
    }

    // ContactGroup ID'ye göre getirme
    inline std::optional<ContactGroup> getContactGroupById(pqxx::connection& conn, int groupId) {
        pqxx::nontransaction txn(conn);
        const std::string query = "SELECT id, group_name, group_surname, email, phone FROM contact_groups WHERE id = $1";

        if (const pqxx::result result = txn.exec_params(query, groupId); !result.empty()) {
            return ContactGroupFactory::createContactGroupFromRow(result[0]);
        }
        return std::nullopt;
    }

    // ContactGroup ekleme
    inline void addContactGroup(pqxx::connection& conn, const std::string& name, const std::string& surname, const std::string& email, const std::string& phone) {
        const std::string query = "INSERT INTO contact_groups (group_name, group_surname, email, phone) VALUES ($1, $2, $3, $4)";
        pqxx::work txn(conn);
        txn.exec_params(query, name, surname, email, phone);
    }

}

#endif

