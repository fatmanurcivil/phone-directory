#ifndef APPLICATION_CONTACT_SERVICE_HPP
#define APPLICATION_CONTACT_SERVICE_HPP

#include <string>
#include <pqxx/pqxx>
#include "../domain/contact_group/contactgroup-service.hpp"
#include "../domain/contact/contact.hpp"
#include "../domain/contact/contact-service.hpp"

namespace ApplicationContactService {

    inline void addContact(pqxx::connection &conn, const std::string& name, const std::string& surname, const std::string& phone, const std::string& email) {
        ContactService::addContact(conn, name, surname, phone, email);
    }
    inline void deleteContact(pqxx::connection &conn, const int contactId) {
        ContactService::deleteContact(conn, contactId);
    }
    inline std::vector<Contact> listContacts(pqxx::connection &conn, const std::optional<int>& id = std::nullopt) {
        return ContactService::listContacts(conn, id);
    }
    inline void updateContact(pqxx::connection &conn, const Contact &contact) {
        ContactService::updateContact(conn, contact);
    }

                       //////////////// CONTACT GROUP/////////////////////////

    inline void deleteContactGroup(pqxx::connection &conn, const int groupId) {
        ContactGroupService::deleteContactGroup(conn, groupId);
    }
    inline std::vector<ContactGroup> getContactGroups(pqxx::connection &conn) {
        return ContactGroupService::getContactGroups(conn);
    }
    inline ContactGroup getContactGroupById(pqxx::connection &conn, const int groupId) {
        return ContactGroupService::getContactGroupById(conn, groupId).value();
    }
    inline void updateContactGroup(pqxx::connection &conn,const int groupId, const std::string &groupName, const std::string &groupSurname, const std::string &email, const std::string &phone) {
    ContactGroupService::updateContactGroup(conn, groupId, groupName, groupSurname, email, phone);
    }
    inline void addContactGroup(pqxx::connection &conn, const std::string &groupName, const std::string &groupSurname, const std::string &email, const std::string &phone) {
        ContactGroupService::addContactGroup(conn, groupName, groupSurname, email, phone);
    }

}
#endif // APPLICATION_CONTACT_SERVICE_HPP