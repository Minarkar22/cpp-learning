#include<iostream>
#include<vector>
#include<string>

std::vector<int> deadfish(const std::string& data){
    int value = 0;
    std::vector<int> output;
    output.reserve(data.size());

    for (char cmd : data){
        switch (cmd){
            case 'i' : value++;     break;
            case 'd' : value--;     break;
            case 's' : value *= value;  break;
            case 'o' : output.push_back(value); break;
            default : break;
        }
    }

    return output;
}

int main(){
    //Test 1
    std::vector<int> test1 = deadfish("iiisdoso");
    std::cout << "Test 1\n";
    for (int n : test1){
        std::cout << n << " ";
        std::cout << std::endl; 
    }

    //Test 2
    std::vector<int> test2 = deadfish("iiisdosodddddiso");
    std::cout << "Test 2\n";
    for (int n : test2){
        std::cout << n << " ";
        std::cout << std::endl; 
    }

    return 0;
}