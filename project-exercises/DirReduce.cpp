#include <iostream>
#include <vector>
#include <string>

bool isOpposite(const std::string& a, const std::string& b){
    return (a == "NORTH" && b == "SOUTH") ||
           (a == "SOUTH" && b == "NORTH") ||
           (a == "EAST" && b == "WEST") ||
           (a == "WEST" && b == "EAST");
}

std::vector<std::string> dirReduce (const std::vector<std::string> & directions){
    std::vector<std::string> stack;

    for (const std::string& dir : directions){
        if (!stack.empty() && isOpposite(stack.back(), dir)){
            stack.pop_back();
        }else {
            stack.push_back(dir);
        }
    }

    return stack;
}

int main() {
    // Test 1
    std::vector<std::string> r1 = dirReduce({"NORTH","SOUTH","SOUTH","EAST","WEST","NORTH","WEST"});
    for (auto& s : r1) std::cout << s << " ";
    std::cout << std::endl; // WEST

    // Test 2
    std::vector<std::string> r2 = dirReduce({"NORTH","SOUTH","EAST","WEST"});
    for (auto& s : r2) std::cout << s << " ";
    std::cout << std::endl; // (empty)

    // Test 3
    std::vector<std::string> r3 = dirReduce({"NORTH","EAST","WEST","SOUTH","WEST","WEST"});
    for (auto& s : r3) std::cout << s << " ";
    std::cout << std::endl; // WEST WEST

    // Test 4 - non reducible
    std::vector<std::string> r4 = dirReduce({"NORTH","WEST","SOUTH","EAST"});
    for (auto& s : r4) std::cout << s << " ";
    std::cout << std::endl; // NORTH WEST SOUTH EAST

    return 0;
}