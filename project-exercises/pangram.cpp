//At first, we need to take input string, 
//in this string ignore numbers and punctuation 
//and spaces, treat to lower case same, create a 
//array size of 26, this changing string into loop , 
//each character in string is between a to z 
#include<iostream>
#include<string>
bool is_pangram(std::string &s);

int main(){

    std::string line;
    std::cout << "Enter you string: ";
    getline(std::cin, line);
    //std::cin.ignore();
    if (is_pangram(line))
    {
        std::cout << "Sentence is pangram.\n";
    }
    else {
        std::cout << "Sentence is not pangram.\n";
    }
    return 0;
}

bool is_pangram(std::string &s){
    bool my_arr [26] = {false};

    for (char ch : s){
        if (isalpha(ch))
        {
            ch = tolower(ch);
            int index = ch - 'a';
            my_arr[index] = true;
        }
        
    }

    for (bool ele: my_arr){
        if (ele == 0){
            return false;
        }
    }
    return true;
    

}