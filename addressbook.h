// AddressBook.h

#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "Contact.h"
#include <vector>
#include <memory>

class AddressBook {
    public:
        AddressBook() = default;
        ~AddressBook() = default;


        // ... (Add, Edit, Delete methods go here)

        void addContact(std::unique_ptr<Contact> newContact); 
        void listAllContacts() const; 
        Contact* viewContact(size_t index); 

        size_t findContactIndex(const std::string& name) const; 

        void editContact(size_t index); 
        void deleteContact(size_t index);
        // Methods for Search and Filtering
        std::vector<const Contact*> searchByName(const std::string &nameQuery) const;
        std::vector<const Contact*> searchByPhoneNumber(const std::string& phoneQuery) const;
        std::vector<const Contact*> searchByEmail(const std::string& emailQuery) const;

        std::vector<const Contact*> filterByType(const std::string &type) const;
        std::vector<const Contact*> filterByCity(const std::string& city) const;
        std::vector<const Contact*> filterByTag(const std::string& tag) const;

        bool saveToFile(const std::string& filename) const;
        bool loadFromFile(const std::string& filename);


        // Reports
        void listContactsByType(const std::string& type) const; 
        void showContactsMissingInfo() const;                    
        void displayGroupSummaries() const;

    private:
        std::vector<std::unique_ptr<Contact>> contacts; 
};

#endif // ADDRESSBOOK_H