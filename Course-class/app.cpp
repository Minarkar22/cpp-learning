#include "Course.h"

int main(){
    try {
        Course c(10, "scores.dat");
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}