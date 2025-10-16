// Person.cpp
#include "Person.h"
#include <iostream>
#include <sstream> 
#include <string>  

// CONSTRUCTOR
Person::Person(const std::string &name, const std::string &phoneNumber, const std::string &email,
               const std::string &address, const std::string &city, const std::string &group,
               const std::string &dob)
    // CALL BASE CLASS CONSTRUCTOR FIRST (REQUIRED)
    : Contact(name, phoneNumber, email, address, city, group),
    // INITIALIZE UNIQUE MEMBER
      dateOfBirth(dob)
{}

// UNIQUE GETTER AND SETTER

const std::string &Person::getDateOfBirth() const
{
    return dateOfBirth;
}

void Person::setDateOfBirth(const std::string &newDateOfBirth)
{
    dateOfBirth = newDateOfBirth;
}


// Returns the specific type identifier
std::string Person::getType() const
{
    return "PERSON";
}

// Outputs all contact details to the console
void Person::displayInfo() const
{
    std::cout << "\n--- Contact Type: PERSON ---\n";
    std::cout << "Name:            " << getName() << "\n";
    std::cout << "Phone:           " << getPhoneNumber() << "\n";
    std::cout << "Email:           " << getEmail() << "\n";
    std::cout << "Address:         " << getAddress() << ", " << getCity() << "\n";
    std::cout << "Group:           " << getGroup() << "\n";
    
    // Display tags
    std::cout << "Tags:            ";
    const auto &currentTags = getTags();
    for (size_t i = 0; i < currentTags.size(); ++i) {
        std::cout << currentTags[i] << (i == currentTags.size() - 1 ? "" : ", ");
    }
    std::cout << "\n";

    // Display unique Person data
    std::cout << "Date of Birth:   " << dateOfBirth << "\n";
    std::cout << "---------------------------------\n";
}

//Converts all contact details (base + unique) into a single string for file saving
std::string Person::serialize() const
{
    // Use a stringstream to build the CSV line
    std::stringstream ss;

    ss << getType() << ",";
    
    // Append all base class data
    ss << getName() << ","
       << getPhoneNumber() << ","
       << getEmail() << ","
       << getAddress() << ","
       << getCity() << ","
       << getGroup() << ",";
    ss << dateOfBirth;
    
    // Optionally append tags as a sub-string (e.g., Tag1|Tag2|Tag3)
    const auto &currentTags = getTags();
    ss << ",";
    for (size_t i = 0; i < currentTags.size(); ++i) {
        ss << currentTags[i] << (i == currentTags.size() - 1 ? "" : "|");
    }

    return ss.str();
}