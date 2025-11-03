#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
// #include <vector>
#include <string>
// #include <expected>
// #include <climits>

class Student {
private:
    std::string _id;
    std::string _name;
    float _gpa;
public:
    std::string id() const;
    std::string name() const;
    float gpa() const;

    void setid(const std::string &input);
    void setName(const std::string &input);
    void setGPA(const float &gpa);
    
    void printInfo();
};

std::istream& operator>>(std::istream& is, Student& sv); 


#endif