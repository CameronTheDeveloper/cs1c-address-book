// Vendor.h
#ifndef VENDOR_H
#define VENDOR_H

#include <string>
#include "Contact.h"

class Vendor : public Contact 
{
    private:
        std::string productOrService;
        std::string accountManager;
        
    public:
        // Constructor
        Vendor(const std::string &name, const std::string &phoneNumber, const std::string &email,
            const std::string &address, const std::string &city, const std::string &group,
            const std::string &productOrService, const std::string &accountManager); 

        // Getters and Setters
        const std::string& getProductOrService() const;
        void setProductOrService(const std::string &newProductOrService);
        
        const std::string& getAccountManager() const;
        void setAccountManager(const std::string &newAccountManager);

        // Overriding
        std::string getType() const override; 
        std::string serialize() const override; 
        void displayInfo() const override; 
};

#endif // VENDOR_H