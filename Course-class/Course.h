#ifndef COURSE_H
#define COURSE_H
#include <iostream>
#include <fstream>

class Course
{
    private:
        int numOfStuds;
        const char* inputFileName;
        std::ifstream inputFile;
        struct Student {int id; int score; char grade; double deviation; };
        Student* students;
        double averageScore;
        double standardDeviation;

        void getInput();
        void setGrade();
        void setAverage();
        void setDeviations();
        void printResult() const;
    public:
        Course(int numofStuds, const char* inputFileName);
        ~Course();

};

#endif