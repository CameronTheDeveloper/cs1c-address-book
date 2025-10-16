// Emergency.cpp
#include "Emergency.h"
#include <iostream>
#include <sstream>
#include <algorithm> 

// CONSTRUCTOR

Emergency::Emergency(const std::string &name, const std::string &phoneNumber, const std::string &email,
                     const std::string &address, const std::string &city, const std::string &group,
                     const std::string &relation, const std::string &criticalNotes)
    : Contact(name, phoneNumber, email, address, city, group),
      relationship(relation),
      notes(criticalNotes)
{}

// GETTERS AND SETTERS

const std::string& Emergency::getRelationship() const
{
    return relationship;
}

void Emergency::setRelationship(const std::string &newRelationship)
{
    relationship = newRelationship;
}

const std::string& Emergency::getNotes() const
{
    return notes;
}

void Emergency::setNotes(const std::string &newNotes)
{
    notes = newNotes;
}

// OVERRIDES

// Returns the specific type identifier
std::string Emergency::getType() const
{
    return "EMERGENCY";
}

// Outputs all contact details
void Emergency::displayInfo() const
{
    std::cout << "\n!!! CONTACT TYPE: EMERGENCY !!!\n";
    std::cout << "Name:              " << getName() << "\n";
    std::cout << "Relationship:      " << relationship << "\n"; 
    std::cout << "CRITICAL NOTES:    " << notes << "\n";        
    std::cout << "Phone (PRIMARY):   " << getPhoneNumber() << "\n";
    std::cout << "Email:             " << getEmail() << "\n";
    std::cout << "Address:           " << getAddress() << ", " << getCity() << "\n";
    
    // Display tags
    std::cout << "Tags:              ";
    const auto& currentTags = getTags();
    for (size_t i = 0; i < currentTags.size(); ++i) {
        std::cout << currentTags[i] << (i == currentTags.size() - 1 ? "" : ", ");
    }
    std::cout << "\n";
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}

// serialize
std::string Emergency::serialize() const
{
    std::stringstream ss;
    
   
    ss << getType() << ",";
    
    ss << getName() << ","
       << getPhoneNumber() << ","
       << getEmail() << ","
       << getAddress() << ","
       << getCity() << ","
       << getGroup() << ",";
       
    ss << relationship << ","
       << notes;
    
    const auto& currentTags = getTags();
    ss << ",";
    for (size_t i = 0; i < currentTags.size(); ++i) {
        ss << currentTags[i] << (i == currentTags.size() - 1 ? "" : "|");
    }

    return ss.str();
}