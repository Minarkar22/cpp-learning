#include<iostream>
#include<string>
bool is_isogram(std::string &s);
int main(){
    std::string word;
    std::cout << "Enter your word: ";
    getline(std::cin, word);
    if(is_isogram(word)){
        std::cout << "Isogram.\n";
    }else{
        std::cout << "Not Isogram.\n";
    }

    return 0;
}


// bool is_isogram(std::string &s)
// {
//     bool my_arr[26] = {false};
//     for (char ele : s)
//     {
//         if(isalpha(ele))
//         {
//             ele = tolower(ele);
//             int index = ele - 'a';
//             if (my_arr[index] == true)
//                 return false;
//             else
//                 my_arr[index] = true;
//         }
//     }

//     return true;
    
// }

bool is_isogram(std::string &s){
    for (int i = 0; i < s.length(); i++){
        for (int j = i + 1; j < s.length(); j++){
            if (tolower(s[i]) == tolower(s[j]))
                return false;
        }
    }

    return true;
}