// Vendor.cpp
#include "Vendor.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// CONSTRUCTOR
Vendor::Vendor(const std::string &name, const std::string &phoneNumber, const std::string &email,
               const std::string &address, const std::string &city, const std::string &group,
               const std::string &product, const std::string &manager)
    : Contact(name, phoneNumber, email, address, city, group),
      productOrService(product),
      accountManager(manager)
{}

// GETTERS AND SETTERS

const std::string& Vendor::getProductOrService() const
{
    return productOrService;
}

void Vendor::setProductOrService(const std::string &newProductOrService)
{
    productOrService = newProductOrService;
}

const std::string &Vendor::getAccountManager() const
{
    return accountManager;
}

void Vendor::setAccountManager(const std::string &newAccountManager)
{
    accountManager = newAccountManager;
}

// OVERRIDES
std::string Vendor::getType() const
{
    return "VENDOR";
}

// Outputs all contact details (base + unique)
void Vendor::displayInfo() const
{
    std::cout << "\n--- Contact Type: VENDOR ---\n";
    std::cout << "Name:              " << getName() << "\n";
    std::cout << "Product/Service:   " << productOrService << "\n"; 
    std::cout << "Account Manager:   " << accountManager << "\n";  
    std::cout << "Phone:             " << getPhoneNumber() << "\n";
    std::cout << "Email:             " << getEmail() << "\n";
    std::cout << "Address:           " << getAddress() << ", " << getCity() << "\n";
    std::cout << "Group:             " << getGroup() << "\n";
    
    // Display tags
    std::cout << "Tags:              ";
    const auto& currentTags = getTags();
    for (size_t i = 0; i < currentTags.size(); ++i) {
        std::cout << currentTags[i] << (i == currentTags.size() - 1 ? "" : ", ");
    }
    std::cout << "\n";
    std::cout << "--------------------------------\n";
}

// Converts all data into a single string for file saving
std::string Vendor::serialize() const
{
    std::stringstream ss;
    
    ss << getType() << ",";
    
    ss << getName() << ","
       << getPhoneNumber() << ","
       << getEmail() << ","
       << getAddress() << ","
       << getCity() << ","
       << getGroup() << ",";
       
    ss << productOrService << ","
       << accountManager;
    
    const auto& currentTags = getTags();
    ss << ",";
    for (size_t i = 0; i < currentTags.size(); ++i) {
        ss << currentTags[i] << (i == currentTags.size() - 1 ? "" : "|");
    }

    return ss.str();
}