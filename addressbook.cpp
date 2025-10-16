// AddressBook.cpp

#include "AddressBook.h"
#include <algorithm>
#include <iostream>

// search function by name
std::vector<const Contact*> AddressBook::searchByName(const std::string& nameQuery) const {
    std::vector<const Contact*> results;
    
    // Iterate over the vector of unique_ptr<Contact>
    for (const auto& contactPtr : contacts) {
        
        // Use the base class getter to access the name field
        std::string contactName = contactPtr->getName();
        
        // Logic: Check if the contact's name contains the search query
        if (contactName.find(nameQuery) != std::string::npos) {
            // Store the raw pointer of the matching contact
            results.push_back(contactPtr.get());
        }
    }
    return results;
}

// filter function using polymorphism
std::vector<const Contact*> AddressBook::filterByType(const std::string& type) const {
    std::vector<const Contact*> results;

    for (const auto& contactPtr : contacts) {
        if (contactPtr->getType() == type) {
            results.push_back(contactPtr.get());
        }
    }
    return results;
}