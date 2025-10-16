// Business.h
#ifndef BUSINESS_H
#define BUSINESS_H

#include <string>
#include "Contact.h"

// The Business class publicly inherits from the Contact class
class Business : public Contact 
{
private:
    std::string industry;
    
public:
    // Constructor
    Business(const std::string &name, const std::string &phoneNumber, const std::string &email,
             const std::string &address, const std::string &city, const std::string &group,
             const std::string &industry); 

    // Getters and Setters for unique members
    
    const std::string &getIndustry() const;
    void setIndustry(const std::string &newIndustry);

    // Overriding
    std::string getType() const override; 
    std::string serialize() const override; 
    void displayInfo() const override; 
};

#endif // BUSINESS_H