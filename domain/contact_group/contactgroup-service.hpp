#ifndef CONTACTGROUP_SERVICE_HPP
#define CONTACTGROUP_SERVICE_HPP

#include "contactgroup-repository.hpp"
#include "contact-group.hpp"
#include <pqxx/pqxx>
#include <optional>
#include <vector>

namespace ContactGroupService {


    inline std::vector<ContactGroup> getContactGroups(pqxx::connection& conn) {
        return ContactGroupRepository::listContactGroups(conn);
    }
    inline std::optional<ContactGroup> getContactGroupById(pqxx::connection& conn, const int groupId) {
        return ContactGroupRepository::getContactGroupById(conn, groupId);
    }
    inline void deleteContactGroup(pqxx::connection& conn, const int groupId) {
        ContactGroupRepository::deleteContactGroup(conn, groupId);
    }
    inline void updateContactGroup(pqxx::connection& conn, const int groupId, const std::string& groupName, const std::string& groupSurname, const std::string& email, const std::string& phone) {
        ContactGroupRepository::updateContactGroup(conn,groupId,groupName, groupSurname, email, phone);
    }
    inline void addContactGroup(pqxx::connection& conn, const std::string& groupName, const std::string& groupSurname, const std::string& email, const std::string& phone) {
        ContactGroupRepository::addContactGroup(conn,groupName,groupSurname,email,phone);
    }


}

#endif
