// AddressBook.cpp

#include "AddressBook.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility> 
#include <fstream>

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

// Filter by tag
std::vector<const Contact*> AddressBook::filterByTag(const std::string& tag) const {
    std::vector<const Contact*> results;
    
    for (const auto& contactPtr : contacts) {
        const std::vector<std::string>& contactTags = contactPtr->getTags();
        
        if (std::find(contactTags.begin(), contactTags.end(), tag) != contactTags.end()) {
            results.push_back(contactPtr.get());
        }
    }
    return results;
}

// Filter by city
std::vector<const Contact*> AddressBook::filterByCity(const std::string& city) const {
    std::vector<const Contact*> results;
    
    for (const auto& contactPtr : contacts) {
        if (contactPtr->getCity() == city) {
            results.push_back(contactPtr.get());
        }
    }
    return results;
}

// Add a new contact
void AddressBook::addContact(std::unique_ptr<Contact> newContact)
{
    if (newContact)
    {
        // std::move transfers ownership of the dynamically allocated object
        contacts.push_back(std::move(newContact));
        std::cout << "Successfully added new contact to the address book.\n";
    }
}


// List all contacts
void AddressBook::listAllContacts() const
{
    if (contacts.empty())
    {
        std::cout << "The address book is currently empty.\n";
        return;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "                    ALL CONTACTS (" << contacts.size() << ")\n";
    std::cout << "=======================================================\n";
    
    std::cout << " Index | Type      | Name                   | Phone Number \n";
    std::cout << "-------------------------------------------------------\n";

    for (size_t i = 0; i < contacts.size(); ++i)
    {
        std::cout << " [" << i << "]   | ";
        std::cout.width(9); std::cout << std::left << contacts[i]->getType() << " | ";
        std::cout.width(22); std::cout << std::left << contacts[i]->getName() << " | ";
        std::cout << contacts[i]->getPhoneNumber() << "\n";
    }
    std::cout << "=======================================================\n";
}

// View a single contact's details
const Contact* AddressBook::viewContact(size_t index) const
{
    // Check for bounds safety
    if (index < contacts.size())
    {
        return contacts[index].get(); 
    }
    return nullptr; 
}


// Returns the index of a contact matching the name.
size_t AddressBook::findContactIndex(const std::string& name) const
{
    for (size_t i = 0; i < contacts.size(); ++i)
    {
        // Case-insensitive comparison is recommended for search/find logic
        std::string contactName = contacts[i]->getName();
        
        // Simple case-sensitive check for now (can be improved later)
        if (contactName == name) 
        {
            return i;
        }
    }
    return contacts.size(); // Indicate failure
}

// Edit contact
void AddressBook::editContact(size_t index)
{
    if (index >= contacts.size())
    {
        std::cout << "Error: Invalid contact index provided for editing.\n";
        return;
    }

    Contact* contactToEdit = contacts[index].get();
    std::cout << "Starting edit for: " << contactToEdit->getName() << "\n";
    std::cout << "The editing logic (calling setters like setName(), setCity(), etc.) must be implemented in the calling function (UI).\n";
    
}

// Delete contact
void AddressBook::deleteContact(size_t index)
{
    if (index >= contacts.size())
    {
        std::cout << "Error: Invalid contact index provided for deletion.\n";
        return;
    }

    std::string deletedName = contacts[index]->getName();

    contacts.erase(contacts.begin() + index);

    std::cout << "Successfully deleted contact: " << deletedName << ".\n";
}


bool AddressBook::saveToFile(const std::string& filename) const
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return false;
    }

    for (const auto& contactPtr : contacts)
    {
        outFile << contactPtr->serialize() << "\n";
    }

    outFile.close();
    std::cout << "Successfully saved " << contacts.size() << " contacts to " << filename << "\n";
    return true;
}


bool AddressBook::loadFromFile(const std::string& filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        std::cerr << "Warning: Could not open file " << filename << ". Starting with an empty address book.\n";
        return false;
    }

    contacts.clear(); 
    std::string line;
    int contactsLoaded = 0;

    while (std::getline(inFile, line))
    {
        if (line.empty()){
            continue;
        } 
    }

    inFile.close();
    std::cout << "Successfully loaded " << contactsLoaded << " contacts from " << filename << "\n";
    return true;
}