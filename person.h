#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <vector>
#include "contact.h"

class Person : public Contact
{
    public:
        Person(const std::string &name, const std::string &phoneNumber, const std::string &email,
            const std::string &city, const std::string &group, const std::string &address, const std::string &dateOfBirth);

        std::string getDateOfBirth() const;
        void setDateOfBirth(const std::string &dateOfBirth);

        std::string getType() const override; 
        std::string serialize() const override; 
        void displayInfo() const override;

    private:
        std::string dateOfBirth;
    };


#endif // PERSON_H