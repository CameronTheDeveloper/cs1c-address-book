#include <iostream>
#include <string>
#include <vector>
#include "contact.h"

Contact::Contact(const std::string &name, const std::string &phoneNumber, const std::string &email,
                 const std::string &city, const std::string &group, const std::string &address)
    : name(name), phoneNumber(phoneNumber), email(email), city(city), group(group), address(address) {}