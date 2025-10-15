#include <iostream>
#include <string>
#include <vector>
#include "contact.h"

Contact::Contact(const std::string &name, const std::string &phoneNumber, const std::string &email,
                 const std::string &city, const std::string &group, const std::string &address)
    : name(name), phoneNumber(phoneNumber), email(email), city(city), group(group), address(address) {}

Contact::~Contact() = default;

void Contact::setName(const std::string &newName)
{
    name = newName;
}

void Contact::setPhoneNumber(const std::string &newPhoneNum)
{
    phoneNumber = newPhoneNum;
}

void Contact::setEmail(const std::string &newEmail)
{
    email = newEmail;
}

void Contact::setCity(const std::string &newCity)
{
    city = newCity;
}

void Contact::setGroup(const std::string &newGroup)
{
    group = newGroup;
}

void Contact::setAddress(const std::string &newAddress)
{
    address = newAddress;
}
