#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
#include "contact.h"

class Person : public Contact
{
public:
    Person(const std::string &name, const std::string &phoneNumber, const std::string &email,
           const std::string &city, const std::string &group, const std::string &address);
};

#endif // PERSON_H