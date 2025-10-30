#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include <expected>
#include <climits>

class Student {
public:
    std::string _id;
    std::string _name;
    float _gpa;
    static std::expected<Student, std::string> getStudentFromKeyboard(std::string message, int maxAttempts);
    static int findMaxGPAStudent(std::vector<Student> vec);
    void printInfo();
};

std::istream& operator>>(std::istream& is, Student& sv); 


#endif