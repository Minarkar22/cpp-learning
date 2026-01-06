#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<limits>
#include<termios.h>
#include<unistd.h>
#include<sstream>
#include<openssl/sha.h>
void RegisterUser();
void LoginUser();
std::string getHiddenPassword();
std::string hashed_sha256(const std::string& str);
using namespace std;

int main()
{
    int option;
    char choice;
    do{
        cout << "============Ha-Ha============\n";
        cout << "1.----------Register---------\n";
        cout << "2.----------Login------------\n";

        cout << "\n-----------Enter your option : ";
    
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(option){
            case 1 :{
                cout << "For Register !\n";
                RegisterUser();
                break;
            } 
           
            case 2 :{
                cout << "For Login !\n";
                LoginUser();
                break;
            }
            default :{
                cout << "Invalid Option. Please Try Again!\n";
                break;
            }
        }
        cout << "Do you want to continue. (Y/N)\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while(choice == 'Y' || choice == 'y');
    

    return 0;
}

//RegisterUser 
//-1. Ask Username 2.Ask Passwd 3.Create File To Store
// 4.Save name and passwd  5. Show Success 6. Need to check user already exist
void RegisterUser(){
    string username;
    string password;
    string hashedPassword;
    
    cout << "Enter Username : ";
    getline(cin, username);
    cout << "Enter Password : ";
    password = getHiddenPassword();
    hashedPassword = hashed_sha256(password);
    
    filesystem::create_directories("databases");
    string filePath = "databases/" + username + ".txt";

    if(username.find_first_not_of(" \t\n\r") == string::npos ||
        password.find_first_not_of(" \t\n\r") == string::npos)
    {
        cout << "Fields cannot be empty!\n";
        return;
    }
    else if(filesystem::exists(filePath))
    {
        cout << "User Already Exist!\n";
        return;
    }
    else{
        ofstream wFile(filePath);
        if (!wFile)
        {
            cout << "No such file and can not open file!\n";
            return;
        }
        wFile << username << endl;
        wFile << hashedPassword << endl;
        wFile.close();
    }
  
    cout << "Success.\n";
    
}


//LoginUser -1. Ask username 2. Ask Passwd 3. Open file 
// 4. Check user input with data stored in file
void LoginUser(){
    string login_username;
    string login_password;
    string login_hash;
    cout << "Enter Username: ";
    getline(cin, login_username);
    cout << "Enter Password: ";
    login_password = getHiddenPassword();
    login_hash = hashed_sha256(login_password);


    string filePath = "databases/" + login_username + ".txt";

    if(!filesystem::exists(filePath)){
        cout << "User does not exist. Please Register First!\n";
        return;
    }
    ifstream rFile(filePath);
    if (!rFile)
    {
        cout << "Can not open file.\n";
        return;
    }
    string storedUsername;
    string storedHash;
    getline(rFile, storedUsername);
    getline(rFile, storedHash);
    rFile.close();

    if(storedUsername == login_username && storedHash == login_hash)
    {
        cout << "Login Successful.\n";
    }
    else{
        cout << "Invalid username and password!\n";
    }
    
}

//To hide password input
string getHiddenPassword()
{
    string password;
    termios oldt;
    termios newt;

    // Get the current terminal attributes
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        throw std::runtime_error("tcgetattr failed");
    }

    // Copy the attributes to a new structure
    newt = oldt;

    // Disable the ECHO flag (local flag for echoing input characters)
    newt.c_lflag &= ~ECHO;

    // Set the new terminal attributes immediately
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0) {
        throw std::runtime_error("tcsetattr failed");
    }

    // Read the password using standard input (std::getline works well here)
    std::getline(std::cin, password);

    // Restore the original terminal attributes
    if (tcsetattr(STDIN_FILENO, TCSANOW, &oldt) != 0) {
        // Handle error, maybe log it, but the program can continue
    }

    return password;
}

//To hesh password
std::string hashed_sha256(const std::string& str) 
{ 
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str.c_str(), str.size(), hash);
    std::stringstream ss; 
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) 
    { ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i]; } 
    return ss.str(); 
}

