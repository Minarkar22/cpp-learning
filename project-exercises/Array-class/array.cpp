#include "array.h"

Array::Array(int cap) : capacity(cap)
{
    size = 0;
    arr = new int[capacity];
}

Array::~Array()
{
    delete [] arr;
}

void Array::insert(int value){
    if (size < capacity){
        arr[size] = value;
        size ++;
    } else {
        std::cout << "Array is Full capacity!\n";
    }
}

void Array::pop(){
    if (size > 0){
        size --;
    }else {
        std::cout << "Array is already empty.\n";
    }
}

void Array::print() const {
    if (size == 0)
    {
        std::cout << "Array is empty.\n";
    }
    for (int i = 0; i < size; i++)
    {
        std::cout << i << ": " << arr[i] << std::endl;
    }

    std::cout << std::endl;
}

int Array::getSize(){
    return size;
}

int Array::getCapacity(){
    return capacity;
}

void Array::sort(){
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}