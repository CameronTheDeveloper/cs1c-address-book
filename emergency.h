// Emergency.h
#ifndef EMERGENCY_H
#define EMERGENCY_H

#include <string>
#include "Contact.h"

class Emergency : public Contact 
{
    private:
        std::string relationship;
        std::string notes;
        
    public:
        // Constructor Declaration
        Emergency(const std::string &name, const std::string &phoneNumber, const std::string &email,
                const std::string &address, const std::string &city, const std::string &group,
                const std::string &relationship, const std::string &notes); 

        // Getters and Setters for unique members
        const std::string& getRelationship() const;
        void setRelationship(const std::string &newRelationship);
        
        const std::string& getNotes() const;
        void setNotes(const std::string &newNotes);

        // Overriding
        std::string getType() const override; 
        std::string serialize() const override; 
        void displayInfo() const override; 
};

#endif // EMERGENCY_H