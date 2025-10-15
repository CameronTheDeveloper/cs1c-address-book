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
    std::string city;
    std::string group;
    std::string address;
    std::vector<std::string> tags;

public:
    Contact(const std::string &name, const std::string &phoneNumber, const std::string &email,
            const std::string &city, const std::string &group, const std::string &address);
    virtual ~Contact() = default;

    virtual std::string getType() const = 0;   // Pure virtual function to make Contact an abstract class
    virtual std::string serialize() const = 0; // Pure virtual function for serialization
    virtual void displayInfo() const = 0;      // Pure virtual function for displaying contact info

    void setName(const std::string &newName);
    void setPhoneNumber(const std::string &newPhoneNum);
    void setEmail(const std::string &newEmail);
    void setCity(const std::string &newCity);
    void setGroup(const std::string &newGroup);
    void setAddress(const std::string &newAddress);
    const std::string &getName() const;
    const std::string &getPhoneNumber() const;
    const std::string &getEmail() const;
    const std::string &getCity() const;
    const std::string &getGroup() const;
    const std::string &getAddress() const;
    const std::vector<std::string> &getTags() const;

    void addTag(const std::string &newTag);
    void removeTag(const std::string &tagToRemove);
};

#endif // CONTACT_H