#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

class Array
{
    private:
        int capacity;
        int size;
        int* arr;
    public:
        Array(int capacity);
        ~Array();
        void insert(int value);
        void pop();
        void print() const;
        int getSize();
        int getCapacity();
        void sort();
};

#endif