// AddressBook.h

#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "Contact.h"
#include <vector>
#include <memory>

class AddressBook {
    public:
        // ... (Add, Edit, Delete methods go here)

        // Methods for Search and Filtering
        std::vector<const Contact*> searchByName(const std::string &nameQuery) const;
        std::vector<const Contact*> filterByType(const std::string &type) const;
        // ... other search/filter methods (by email, phone, city, tag)
        
        // ... (Save, Load, List methods go here)

    private:
        std::vector<std::unique_ptr<Contact>> contacts; 
};

#endif // ADDRESSBOOK_H