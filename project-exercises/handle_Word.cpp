#include <iostream>
#include <string>
#include <sstream>


std::string pigIt(const std::string& text){
    std::istringstream stream(text);
    std::string result, word;

    while (stream >> word){
        if (isalpha(word[0])){
            word = word.substr(1) + word[0] + "ay";
        }

        if (!result.empty())
            result += " ";
        result += word;
    }
    return result;
}

int main(){

    std::string text = "Pig latin is cool !";
    std::string new_word = pigIt(text);
    std::cout << new_word << "\n";
    return 0;
}