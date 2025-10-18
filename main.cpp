#include "AddressBook.h"
#include "Person.h"
#include "Business.h"
#include "Vendor.h"
#include "Emergency.h"

#include <iostream>
#include <limits>   
#include <algorithm>
#include <cctype>   
#include <sstream>

const std::string FILENAME = "contacts.csv";

// Prototypes 
void displayMainMenu();
int getMenuChoice(int max);
void pressEnterToContinue();
std::string getRequiredInput(const std::string& prompt);

// Handlers
void handleAddContact(AddressBook& book);
void handleEditContact(AddressBook& book);
void handleSearchFilter(AddressBook& book);
void displaySearchResults(const std::vector<const Contact*>& results, const std::string& title);

// MAIN 
int main()
{
    AddressBook book;
    
    std::cout << "Loading Address Book...\n";
    book.loadFromFile(FILENAME);

    int choice;
    do
    {
        displayMainMenu();
        choice = getMenuChoice(9);

        try 
        {
            switch (choice)
            {
                // Contacts
                case 1: handleAddContact(book); break;
                case 2: handleEditContact(book); break;
                case 3: 
                {
                    book.listAllContacts();
                    std::cout << "Enter the index of the contact to delete: ";
                    size_t index = 0;
                    if (std::cin >> index) {
                        book.deleteContact(index);
                    } else {
                        std::cerr << "Invalid input.\n";
                    }
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                case 4: book.listAllContacts(); break;

                // Searching and Filtering
                case 5: handleSearchFilter(book); break;

                // Reports
                case 6: book.listContactsByType("PERSON"); break;
                case 7: book.displayGroupSummaries(); break;     
                case 8: book.showContactsMissingInfo(); break;   

                // 4. Import/Export
                case 9:
                    std::cout << "Exiting Address Book. Saving data...\n";
                    book.saveToFile(FILENAME);
                    break;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "An unexpected error occurred: " << e.what() << '\n';
        }
        
        if (choice != 9) {
            pressEnterToContinue();
        }

    } while (choice != 9);

    return 0;
}

// UI AND INPUT HELPERs

void displayMainMenu()
{
    std::cout << "\n========================================\n";
    std::cout << "          ADDRESS BOOK MAIN MENU\n";
    std::cout << "========================================\n";
    std::cout << "1. Add New Contact\n";
    std::cout << "2. Edit Existing Contact\n";
    std::cout << "3. Delete Contact\n";
    std::cout << "4. List All Contacts (Brief)\n";
    std::cout << "----------------------------------------\n";
    std::cout << "5. Search and Filter Contacts\n";
    std::cout << "----------------------------------------\n";
    std::cout << "6. Report: Contacts by Type (PERSON)\n";
    std::cout << "7. Report: Group Summaries\n";
    std::cout << "8. Report: Missing Info\n";
    std::cout << "----------------------------------------\n";
    std::cout << "9. Exit (Saves Contacts)\n";
    std::cout << "Enter choice: ";
}

int getMenuChoice(int max)
{
    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > max)
    {
        std::cout << "Invalid choice. Enter a number between 1 and " << max << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    return choice;
}

void pressEnterToContinue()
{
    std::cout << "\nPress ENTER to return to the menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cin.get();
}

std::string getRequiredInput(const std::string& prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

void displaySearchResults(const std::vector<const Contact*>& results, const std::string& title)
{
    std::cout << "\n=======================================================\n";
    std::cout << "          " << title << " (" << results.size() << ")\n";
    std::cout << "=======================================================\n";
    
    if (results.empty()) {
        std::cout << "No matching contacts found.\n";
        return;
    }

    for (const Contact* contact : results)
    {
        contact->displayInfo();
    }
}

// HANDLERS 

void handleAddContact(AddressBook& book)
{
    std::cout << "\n--- ADD NEW CONTACT ---\n";
    std::cout << "Select Type: (P)erson, (B)usiness, (V)endor, (E)mergency: ";
    char typeChar;
    std::cin >> typeChar;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    std::string type = "";
    if (std::toupper(typeChar) == 'P') type = "PERSON";
    else if (std::toupper(typeChar) == 'B') type = "BUSINESS";
    else if (std::toupper(typeChar) == 'V') type = "VENDOR";
    else if (std::toupper(typeChar) == 'E') type = "EMERGENCY";
    else {
        std::cout << "Invalid contact type selected.\n";
        return;
    }

    // 
    std::cout << "\n-- Base Contact Details --\n";
    std::string name = getRequiredInput("  Name: ");
    std::string phone = getRequiredInput("  Phone Number: ");
    std::string email = getRequiredInput("  Email: ");
    std::string address = getRequiredInput("  Street Address: ");
    std::string city = getRequiredInput("  City: ");
    std::string group = getRequiredInput("  Group (e.g., Work, Family): ");
    
    // 
    std::unique_ptr<Contact> newContact = nullptr;

    std::cout << "\n-- Unique Details for " << type << " --\n";

    if (type == "PERSON") {
        std::string dob = getRequiredInput("  Date of Birth (YYYY-MM-DD): ");
        newContact = std::make_unique<Person>(name, phone, email, address, city, group, dob);
    }
    else if (type == "BUSINESS") {
        std::string industry = getRequiredInput("  Industry: ");
        newContact = std::make_unique<Business>(name, phone, email, address, city, group, industry);
    }
    else if (type == "VENDOR") {
        std::string product = getRequiredInput("  Product/Service: ");
        std::string manager = getRequiredInput("  Account Manager: ");
        newContact = std::make_unique<Vendor>(name, phone, email, address, city, group, product, manager);
    }
    else if (type == "EMERGENCY") {
        std::string relation = getRequiredInput("  Relationship: ");
        std::string notes = getRequiredInput("  Critical Notes: ");
        newContact = std::make_unique<Emergency>(name, phone, email, address, city, group, relation, notes);
    }

    // --- Add Tags 
    if (newContact) {
        std::string tagsStr = getRequiredInput("\n  Tags (comma-separated, e.g., VIP, Old Client - optional): ");
        if (!tagsStr.empty()) {
            std::stringstream ss(tagsStr);
            std::string tag;
            while (std::getline(ss, tag, ',')) {
                // Trim leading/trailing whitespace
                tag.erase(0, tag.find_first_not_of(" \t\n\r\f\v"));
                tag.erase(tag.find_last_not_of(" \t\n\r\f\v") + 1);
                if (!tag.empty()) {
                    newContact->addTag(tag);
                }
            }
        }
        book.addContact(std::move(newContact));
    }
}

void handleEditContact(AddressBook& book)
{
    // List contacts and get index
    book.listAllContacts();
    std::cout << "Enter the index of the contact to edit: ";
    size_t index;
    if (!(std::cin >> index)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Contact* contactToEdit = book.viewContact(index);
    if (!contactToEdit) {
        std::cout << "Error: Index " << index << " not found.\n";
        return;
    }

    // Display current info and prompt for base fields
    std::cout << "\n--- EDITING: " << contactToEdit->getName() << " (Type: " << contactToEdit->getType() << ") ---\n";
    std::cout << "Leave field blank to keep current value.\n";

    std::string newName = getRequiredInput("  New Name [" + contactToEdit->getName() + "]: ");
    if (!newName.empty()) contactToEdit->setName(newName);
    
    std::string newPhone = getRequiredInput("  New Phone [" + contactToEdit->getPhoneNumber() + "]: ");
    if (!newPhone.empty()) contactToEdit->setPhoneNumber(newPhone);
    
    std::string newEmail = getRequiredInput("  New Email [" + contactToEdit->getEmail() + "]: ");
    if (!newEmail.empty()) contactToEdit->setEmail(newEmail);
    
    std::string newAddress = getRequiredInput("  New Address [" + contactToEdit->getAddress() + "]: ");
    if (!newAddress.empty()) contactToEdit->setAddress(newAddress);

    std::string newCity = getRequiredInput("  New City [" + contactToEdit->getCity() + "]: ");
    if (!newCity.empty()) contactToEdit->setCity(newCity);

    std::string newGroup = getRequiredInput("  New Group [" + contactToEdit->getGroup() + "]: ");
    if (!newGroup.empty()) contactToEdit->setGroup(newGroup);


    // Edit unique fields using dynamic_cast
    std::cout << "\n-- Editing Type-Specific Fields --\n";
    if (contactToEdit->getType() == "PERSON") {
        Person* p = dynamic_cast<Person*>(contactToEdit);
        std::string newDob = getRequiredInput("  New DOB [" + p->getDateOfBirth() + "]: ");
        if (!newDob.empty()) p->setDateOfBirth(newDob);
    }
    else if (contactToEdit->getType() == "BUSINESS") {
        Business* b = dynamic_cast<Business*>(contactToEdit);
        std::string newIndustry = getRequiredInput("  New Industry [" + b->getIndustry() + "]: ");
        if (!newIndustry.empty()) b->setIndustry(newIndustry);
    }
    else if (contactToEdit->getType() == "VENDOR") {
        Vendor* v = dynamic_cast<Vendor*>(contactToEdit);
        std::string newProduct = getRequiredInput("  New Product/Service [" + v->getProductOrService() + "]: ");
        if (!newProduct.empty()) v->setProductOrService(newProduct);
        std::string newManager = getRequiredInput("  New Account Manager [" + v->getAccountManager() + "]: ");
        if (!newManager.empty()) v->setAccountManager(newManager);
    }
    else if (contactToEdit->getType() == "EMERGENCY") {
        Emergency* e = dynamic_cast<Emergency*>(contactToEdit);
        std::string newRelation = getRequiredInput("  New Relationship [" + e->getRelationship() + "]: ");
        if (!newRelation.empty()) e->setRelationship(newRelation);
        std::string newNotes = getRequiredInput("  New Critical Notes [" + e->getNotes() + "]: ");
        if (!newNotes.empty()) e->setNotes(newNotes);
    }
    
    std::cout << "\nEdit complete for " << contactToEdit->getName() << ".\n";
}

void handleSearchFilter(AddressBook& book)
{
    std::cout << "\n--- SEARCH & FILTER MENU ---\n";
    std::cout << "1. Search by Name (contains)\n";
    std::cout << "2. Search by Phone Number (contains)\n";
    std::cout << "3. Search by Email (contains)\n";
    std::cout << "4. Filter by Type\n";
    std::cout << "5. Filter by City\n";
    std::cout << "6. Filter by Tag\n";
    std::cout << "7. Back to Main Menu\n";
    std::cout << "Enter search choice: ";

    int choice = getMenuChoice(7);
    std::string query;
    std::vector<const Contact*> results;

    if (choice >= 1 && choice <= 6) {
        if (choice >= 1 && choice <= 3) {
            query = getRequiredInput("Enter search query: ");
        } else {
            query = getRequiredInput("Enter filter value: ");
        }

        switch (choice)
        {
            case 1: results = book.searchByName(query); break;
            case 2: results = book.searchByPhoneNumber(query); break;
            case 3: results = book.searchByEmail(query); break;
            case 4: results = book.filterByType(query); break;
            case 5: results = book.filterByCity(query); break;
            case 6: results = book.filterByTag(query); break;
        }

        displaySearchResults(results, "Search/Filter Results");
    }
}