// AddressBook.cpp

#include "AddressBook.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility> 
#include <fstream>
#include <map>     
#include <iomanip> 

#include "Person.h"
#include "Business.h"
#include "Vendor.h"
#include "Emergency.h"

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

// Search contacts by phone number
std::vector<const Contact*> AddressBook::searchByPhoneNumber(const std::string& phoneQuery) const {
    std::vector<const Contact*> results;
    
    for (const auto& contactPtr : contacts) {
        if (contactPtr->getPhoneNumber().find(phoneQuery) != std::string::npos) {
            results.push_back(contactPtr.get());
        }
    }
    return results;
}

// Search contacts by email
std::vector<const Contact*> AddressBook::searchByEmail(const std::string& emailQuery) const {
    std::vector<const Contact*> results;
    
    for (const auto& contactPtr : contacts) {
        if (contactPtr->getEmail().find(emailQuery) != std::string::npos) {
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
        std::string contactName = contacts[i]->getName();
        
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

// Help read seperate parts of file
std::vector<std::string> tokenize(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    
    std::stringstream ss(str);
    
    while (std::getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    
    return tokens;
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
        if (line.empty()) continue;

        std::vector<std::string> fields = tokenize(line, ','); 
        
        if (!fields.empty()) 
        {
            std::unique_ptr<Contact> contact = createContactFromFields(fields);
            
            if (contact) 
            {
                if (fields.size() > 7) { 
                    std::string tagString = fields.back();
                    if (!tagString.empty()) {
                        std::vector<std::string> tags = tokenize(tagString, '|');
                        for (const auto& tag : tags) {
                            if (!tag.empty()) {
                                contact->addTag(tag);
                            }
                        }
                    }
                }
                
                contacts.push_back(std::move(contact));
                contactsLoaded++;
            }
        }
    }

    inFile.close();
    std::cout << "Successfully loaded " << contactsLoaded << " contacts from " << filename << "\n";
    return true;
}

// Helper function for file I/O
// the process of loading data from a file and correctly recreating the objects is complex and requires several steps
std::unique_ptr<Contact> createContactFromFields(const std::vector<std::string>& fields) 
{
    if (fields.empty()) {
        return nullptr;
    } 
    const std::string type = fields[0];
    
    if (fields.size() < 7){
        return nullptr; 
    } 
    
    
    // Extract Base Fields 
    const std::string& name = fields[1];
    const std::string& phone = fields[2];
    const std::string& email = fields[3];
    const std::string& address = fields[4];
    const std::string& city = fields[5];
    const std::string& group = fields[6];
    
    if (type == "PERSON" && fields.size() >= 8) {
        return std::make_unique<Person>(name, phone, email, address, city, group, fields[7]);
    }
    else if (type == "BUSINESS" && fields.size() >= 8) {
        return std::make_unique<Business>(name, phone, email, address, city, group, fields[7]);
    }
    else if (type == "VENDOR" && fields.size() >= 9) {
        return std::make_unique<Vendor>(name, phone, email, address, city, group, fields[7], fields[8]);
    }
    else if (type == "EMERGENCY" && fields.size() >= 9) {
        return std::make_unique<Emergency>(name, phone, email, address, city, group, fields[7], fields[8]);
    }
    
    std::cerr << "Warning: Skipping line with unknown type or missing fields: " << type << "\n";
    return nullptr;
}

// REPORT IMPLEMENTATIONS

// List contacts by type
void AddressBook::listContactsByType(const std::string& type) const
{
    std::vector<const Contact*> filteredList = filterByType(type);

    std::cout << "\n=======================================================\n";
    std::cout << "          REPORT: CONTACTS OF TYPE '" << type << "' (" << filteredList.size() << ")\n";
    std::cout << "=======================================================\n";
    
    if (filteredList.empty()) {
        std::cout << "No contacts found for type: " << type << ".\n";
        return;
    }

    // Display the details of the filtered contacts
    for (const Contact* contact : filteredList)
    {
        contact->displayInfo(); 
    }
}

// Show contacts missing phone number or email
void AddressBook::showContactsMissingInfo() const
{
    std::vector<const Contact*> missingInfoList;

    for (const auto& contactPtr : contacts)
    {
        // Check for missing data (empty string)
        bool phoneMissing = contactPtr->getPhoneNumber().empty();
        bool emailMissing = contactPtr->getEmail().empty();
        
        // If EITHER is missing, add to the report list
        if (phoneMissing || emailMissing)
        {
            missingInfoList.push_back(contactPtr.get());
        }
    }

    std::cout << "\n=======================================================\n";
    std::cout << "         REPORT: CONTACTS MISSING PHONE/EMAIL (" << missingInfoList.size() << ")\n";
    std::cout << "=======================================================\n";

    if (missingInfoList.empty()) {
        std::cout << "All contacts have both a phone number and an email address!\n";
        return;
    }
    
    // Display the details of the missing contacts
    for (const Contact* contact : missingInfoList)
    {
        contact->displayInfo();
    }
}

// Display group summaries
void AddressBook::displayGroupSummaries() const
{
    std::map<std::string, int> groupCounts;

    for (const auto& contactPtr : contacts)
    {
        std::string group = contactPtr->getGroup();
        groupCounts[group]++;
    }

    std::cout << "\n=======================================================\n";
    std::cout << "             REPORT: CONTACTS GROUP SUMMARY\n";
    std::cout << "=======================================================\n";

    if (groupCounts.empty()) {
        std::cout << "The address book is empty or no groups have been assigned.\n";
        return;
    }

    for (const auto& pair : groupCounts)
    {
        std::cout << "Group: " << std::left << std::setw(15) << pair.first 
                  << " | Count: " << pair.second << "\n";
    }
    std::cout << "=======================================================\n";
}