#include <iostream>
#include <string>
#include <vector>
#include "contact.h"

Contact::Contact(const std::string &name, const std::string &phoneNumber, const std::string &email,
                 const std::string &city, const std::string &group, const std::string &address)
    : name(name), phoneNumber(phoneNumber), email(email), city(city), group(group), address(address) {}

Contact::~Contact() = default;

// Setter methods
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

// Getter methods
const std::string &Contact::getName() const
{
    return name;
}

const std::string &Contact::getPhoneNumber() const
{
    return phoneNumber;
}

const std::string &Contact::getEmail() const
{
    return email;
}

const std::string &Contact::getCity() const
{
    return city;
}

const std::string &Contact::getGroup() const
{
    return group;
}

const std::string &Contact::getAddress() const
{
    return address;
}

// Tag management methods
void Contact::addTag(const std::string &newTag)
{
    tags.push_back(newTag);
}

void Contact::removeTag(const std::string &tagToRemove)
{
    auto it = std::find(tags.begin(), tags.end(), tagToRemove);
    if (it != tags.end())
    {
        tags.erase(it);
    }
}
