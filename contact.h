#ifndef CONTACT_H
#define CONTACT_H
#include <string>
#include <vector>

class Contact
{
private:
    std::string name;
    std::string phoneNumber;
    std::string email;
    std::string contactType;
    std::string city;
    std::string group;
    std::vector<std::string> tags;

public:
    Contact(const std::string &name, const std::string &phoneNumber, const std::string &email, const std::string &contactType);
    virtual ~Contact() = default;

    virtual std::string getType() const = 0;   // Pure virtual function to make Contact an abstract class
    virtual std::string serialize() const = 0; // Pure virtual function for serialization
    virtual void displayInfo() const = 0;      // Pure virtual function for displaying contact info

    bool contactTypeIsValid(const std::string &contactTypeInput);
    void setName(const std::string &newName);
    void setPhoneNumber(const std::string &newPhoneNum);
    void setEmail(const std::string &newEmail);
    void setContactType(const std::string &newContactType);
    void setCity(const std::string &newCity);
    void setGroup(const std::string &newGroup);
    std::string getName();
    std::string getPhoneNumber();
    std::string getEmail();
    std::string getContactType();
    std::string getCity();
    std::string getGroup();

    void addTag(const std::string &newTag);
    void removeTag(const std::string &tagToRemove);
};

#endif // CONTACT_H