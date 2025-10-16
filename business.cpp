// Business.cpp
#include "Business.h"
#include <iostream>
#include <sstream>

// CONSTRUCTOR
Business::Business(const std::string &name, const std::string &phoneNumber, const std::string &email,
                   const std::string &address, const std::string &city, const std::string &group,
                   const std::string &industryType)
    : Contact(name, phoneNumber, email, address, city, group),
      industry(industryType) // Only industry initialized here
{}

// GETTER AND SETTER
const std::string& Business::getIndustry() const
{
    return industry;
}

void Business::setIndustry(const std::string &newIndustry)
{
    industry = newIndustry;
}

// Returns the specific type identifier
std::string Business::getType() const
{
    return "BUSINESS";
}

// Outputs all contact details
void Business::displayInfo() const
{
    std::cout << "\n--- Contact Type: BUSINESS ---\n";
    std::cout << "Name:            " << getName() << "\n";
    std::cout << "Industry:        " << industry << "\n"; 
    std::cout << "Phone:           " << getPhoneNumber() << "\n";
    std::cout << "Email:           " << getEmail() << "\n";
    std::cout << "Address:         " << getAddress() << ", " << getCity() << "\n";
    std::cout << "Group:           " << getGroup() << "\n";
    
    // Display tags
    std::cout << "Tags:            ";
    const auto& currentTags = getTags();
    for (size_t i = 0; i < currentTags.size(); ++i) {
        std::cout << currentTags[i] << (i == currentTags.size() - 1 ? "" : ", ");
    }
    std::cout << "\n";
    std::cout << "--------------------------------\n";
}

// Converts all data into a single string for file saving
std::string Business::serialize() const
{
    std::stringstream ss;
    
    // Start with Type Identifier
    ss << getType() << ",";
    
    // Append all base class data
    ss << getName() << ","
       << getPhoneNumber() << ","
       << getEmail() << ","
       << getAddress() << ","
       << getCity() << ","
       << getGroup() << ",";
       
    ss << industry; 
    
    // Append tags
    const auto& currentTags = getTags();
    ss << ",";
    for (size_t i = 0; i < currentTags.size(); ++i) {
        ss << currentTags[i] << (i == currentTags.size() - 1 ? "" : "|");
    }

    return ss.str();
}