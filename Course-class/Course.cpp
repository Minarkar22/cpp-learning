#include "Course.h"
#include <iomanip>
#include <cmath>

Course::Course(int num, const char* ifn) : numOfStuds(num), inputFileName(ifn){
    inputFile.open(inputFileName);
    if (!inputFile){
        throw std::runtime_error("Error! Can't open file: " + std::string(ifn));
    }
    students = new Student[numOfStuds];
    getInput();
    setGrade();
    setAverage();
    setDeviations();
    printResult();
}

Course::~Course(){
    delete [] students;
    inputFile.close();
}

void Course::getInput(){
    for (int i = 0; i < numOfStuds; i++){
        inputFile >> students[i].id;
        inputFile >> students[i].score;
    }
}

void Course::setGrade(){
    char charGrade[] = {'F', 'F', 'F', 'F', 'F', 'F', 'D', 'C', 'B', 'A', 'A'};
    for (int i = 0; i < numOfStuds; i++){
        int index = students[i].score/10;
        students[i].grade = charGrade[index];
    }
}

void Course::setAverage(){
    int sum = 0;
    for (int i = 0; i < numOfStuds; i++){
        sum += students[i].score;
        averageScore = static_cast<double> (sum)/numOfStuds;
    }
}

void Course::setDeviations(){
    standardDeviation = 0.0;
    for(int i = 0; i < numOfStuds; i++){
        students[i].deviation = students[i].score - averageScore;
        standardDeviation += pow(students[i].deviation, 2);
    }
    standardDeviation = sqrt(standardDeviation)/numOfStuds;
}

void Course::printResult()const {
    std::cout << std::endl;
    for (int i = 0; i < numOfStuds; i++){
        std::cout << std::noshowpoint << std::noshowpos;
        std::cout << "ID : "<< students[i].id << std::endl;
        //std::cout << std::setw(14) << std::noshowpoint << std::noshowpos;
        std::cout << "Score : " << students[i].score << std::endl;
        std::cout << "Grade :" << students[i].grade << std::endl;
        //std::cout << std::fixed << std::setw(20) << std::right << std::setprecision(2);
        //std::cout << std::showpoint << std::showpos;
        std::cout <<"Deviation :" << students[i].deviation << std::endl;
    }
    std::cout << "Average Score: " << std::fixed << std::setw(4);
    std::cout << std::setprecision(2) << averageScore << std::endl;
    std::cout << "Standard Deviation: " << standardDeviation ;
}