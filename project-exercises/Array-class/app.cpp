#include "array.h"

int main(){
    Array arr1(5);
    arr1.print();

    arr1.insert(50);
    arr1.insert(30);
    arr1.insert(40);
    arr1.insert(20);
    arr1.insert(10);
    arr1.print();
    std::cout << "Size : " << sizeof(arr1) << std::endl;
    std::cout << "To know number of element: getSize() : " << arr1.getSize() << std::endl;
    std::cout << "To know capacity of array: getCapacity() : " << arr1.getCapacity() << std::endl;
    arr1.pop();
    arr1.print();
    std::cout << "Size : " << sizeof(arr1) << std::endl;
    std::cout << "To know number of element: getSize() : " << arr1.getSize() << std::endl;
    std::cout << "To know capacity of array: getCapacity() : " << arr1.getCapacity() << std::endl;

    arr1.sort();
    arr1.print();
    return 0;
}