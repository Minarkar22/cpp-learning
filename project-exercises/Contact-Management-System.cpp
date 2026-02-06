#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

//Contact
class Contact {
    private:
        int id;
        std::string name;
        std::string ph_number;
        std::string email;
    public:
        Contact() {};
        Contact (int id, std::string name, std::string ph_number, std::string email)
        : id(id), name(name), ph_number(ph_number), email(email) {};
        
    //getter
        int getID () const { return id; }
        std::string getName () const { return name; }
        std::string getNumber () const { return ph_number; }
        std::string getEmail () const { return email; }
    //setter
        void setName (const std::string& n) { name = n; }
        void setNumber (const std::string& p) { ph_number = p; }
        void setEmail (const std::string& e) { email = e; }

};

//Contact-Management
class ContactManager {
    private:
        std::vector<Contact> mycontacts;
    public:
        void addContact();
        void viewContact();
        void searchContact();
        void updateContact();
        void deleteContact();
        void saveToFile();
        void loadFromFile();
        Contact* findById(int id);
};

int main(){
    ContactManager contact_list;
    contact_list.loadFromFile();
    char choice;
    do {
        std::cout << "__________Menu__________\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Show All Contacts\n";
        std::cout << "3. Search Contact\n";
        std::cout << "4. Update Contact\n";
        std::cout << "5. Delete Contact\n";
        std::cout << "6. Save and Exit\n";
        std::cout << "________________________\n";
        std::cout << "Enter your choice: ";
        
        int option;
        std::cin >> option;
        std::cin.ignore();
        switch (option){
            case 1 : {
                std::cout << "Add new contact ...\n";
                contact_list.addContact();
                break;
            }
            case 2 : {
                std::cout << "Show all contacts ...\n";
                contact_list.viewContact();
                break;
            }
            case 3 : {
                std::cout << "Search contact ...\n";
                contact_list.searchContact();
                break;
            }
            case 4 : {
                std::cout << "Update contact ...\n";
                contact_list.updateContact();
                break;
            }
            case 5 : {
                std::cout << "Delete contact ...\n";
                contact_list.deleteContact();
                break;
            }
            case 6 : {
                std::cout << "Save & Exit ...\n";
                contact_list.saveToFile();
                break;
            }
            default : {
                std::cout << "Invalid Option!Please try again.\n";
                break;
            }
        }
        std::cout << "Do you want to continue? y/n\n";
        std::cin >> choice;
        std::cin.ignore();
    } while (choice == 'Y' || choice == 'y');

    return 0;
}

void ContactManager :: addContact(){
    int id;
    std::string name, phoneNumber, email;

    std::cout << "Enter the id of contact: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter Name : ";
    std::getline(std::cin, name);

    std::cout << "Enter Phone number : ";
    std::getline(std::cin, phoneNumber);

    std::cout << "Enter email : ";
    std::getline(std::cin, email);

    mycontacts.emplace_back(id, name, phoneNumber, email);
}

void ContactManager :: viewContact(){
    for (const auto& contact : mycontacts){
        std::cout << contact.getID() << ", ";
        std::cout << contact.getName() << ", ";
        std::cout << contact.getNumber() << ", ";
        std::cout << contact.getEmail() << std::endl;
    }
}

Contact* ContactManager :: findById(int id) {
    for (auto& contact : mycontacts){
        if (contact.getID() == id) return &contact;
    }

    return nullptr;
}

void ContactManager :: searchContact(){
    int search_ID;
    std::cout << "Enter ID to search: ";
    std::cin >> search_ID;
    std::cin.ignore();

    Contact* contact_ID = findById(search_ID);
    if (contact_ID){
        std::cout << "ID : "<< contact_ID->getID() << std::endl;
        std::cout << "Name : "<< contact_ID->getName() << std::endl;
        std::cout << "Phone Number : " << contact_ID->getNumber() << std::endl;
        std::cout << "Email : "<< contact_ID->getEmail() << std::endl;
    }else {
        std::cout << "Contact Not Found.\n";
    }
}

void ContactManager :: updateContact(){
    int search_ID;
    std::cout << "Enter ID to Update: ";
    std::cin >> search_ID;
    std::cin.ignore();

    Contact* contact_ID = findById(search_ID);
    if (contact_ID){
        std::cout << "Contact Info for ID - " << contact_ID ->getID() << " : \n";
        std::cout << "Name : "<< contact_ID->getName() << std::endl;
        std::cout << "Phone Number : " << contact_ID->getNumber() << std::endl;
        std::cout << "Email : "<< contact_ID->getEmail() << std::endl;
    }else {
        std::cout << "Not Found.\n";
        return ;
    }

    int option;
    std::string update_Name;
    std::string update_phNumber;
    std::string update_Email;
    
    std::cout << "__________Menu__________\n";
    std::cout << "1. To Update Name\n";
    std::cout << "2. To Update Phone Number\n";
    std::cout << "3. To Update Email\n";
    std::cout << "________________________\n";
    std::cout << "Enter the option to update: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (option == 1){
        std::cout << "Enter a new Name: ";
        std::getline(std::cin, update_Name);
        contact_ID->setName(update_Name);
    }
    else if (option == 2)
    {
        std::cout << "Enter a new Phone NUmber: ";
        std::getline(std::cin, update_phNumber);
        contact_ID->setNumber(update_phNumber);
    }
    else if (option == 3){
        std::cout << "Enter a new Email: ";
        std::getline(std::cin, update_Email);
        contact_ID->setEmail(update_Email);
    } else {
        std::cout << "Invalid Option!\n";
        return;
    }

    std::cout << "Update Successfully!\n";
}

void ContactManager :: deleteContact(){
    int delete_ID = 0;
    std::cout << "Enter Contact ID to delete: ";
    std::cin >> delete_ID;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Contact* contact = findById(delete_ID);
     if (contact){
        std::cout << "Contact Info for ID - " << contact ->getID() << " : \n";
        std::cout << "Name : "<< contact->getName() << std::endl;
        std::cout << "Phone Number : " << contact->getNumber() << std::endl;
        std::cout << "Email : "<< contact->getEmail() << std::endl;
    }else {
        std::cout << "Not Found.\n";
        return ;
    }
    auto it = mycontacts.begin();
    for (; it != mycontacts.end(); it++){
        if (it->getID() == contact->getID())
            break;
    }
    if (it != mycontacts.end()){
        mycontacts.erase(it);
        std::cout << "Deleted Contact Successfully!\n";
    }
}

void ContactManager :: saveToFile(){
    std::ofstream saveFile("contact.csv");
    if (!saveFile){
        std::cout << "Error! Can't open file!\n";
        return;
    } 

    for (const auto& contact : mycontacts){
        int id = contact.getID();
        std::string name = contact.getName();
        std::string number = contact.getNumber();
        std::string mail = contact.getEmail();

        saveFile << id << "," << name << "," << number << "," << mail << std::endl;
    }

    saveFile.close();

    std::cout << "Save " << mycontacts.size() << " of contact saved successfully!\n";
}

void ContactManager :: loadFromFile(){
    mycontacts.clear();
    std::ifstream loadFile("contact.csv");
    if (!loadFile){
        std::cout << "Error! Can't open file!\n";
        return;
    }

    std::string line;
    while(getline(loadFile, line)){
        if (line.empty()) continue;
        int contact_ID;
        std::string contact_Name;
        std::string contact_Number;
        std::string contact_mail;
        std::stringstream ss(line);
        std::string temp;
        //ID
        if (!getline(ss, temp, ',')) continue;

        try {
            contact_ID = std::stoi(temp);
        } catch (...) {
            std::cout << "Invalid ID. Skipping line.\n";
            continue;
        }
        //Name
        std::getline(ss, contact_Name, ',');
        //Number
        std::getline(ss, contact_Number, ',');
        //Mail
        std::getline(ss, contact_mail, ',');

        mycontacts.emplace_back(
            contact_ID, contact_Name, contact_Number, contact_mail
        );
    }
    loadFile.close();
    std::cout << "Loaded " << mycontacts.size() << " contact from file successfully!\n";
}