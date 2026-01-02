#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<limits>
void RegisterUser();
void LoginUser();
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
    
    cout << "Enter Username : ";
    getline(cin, username);
    cout << "Enter Password : ";
    getline(cin, password);

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
        wFile << password << endl;
        wFile.close();
    }
  
    cout << "Success.\n";
    
}


//LoginUser -1. Ask username 2. Ask Passwd 3. Open file 
// 4. Check user input with data stored in file
void LoginUser(){
    string login_username;
    string login_password;
    cout << "Enter Username: ";
    getline(cin, login_username);
    cout << "Enter Password: ";
    getline(cin, login_password);

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
    string storedPasswd;
    getline(rFile, storedUsername);
    getline(rFile, storedPasswd);
    rFile.close();

    if(storedUsername == login_username && storedPasswd == login_password)
    {
        cout << "Login Successful.\n";
    }
    else{
        cout << "Invalid username and password!\n";
    }
    
}