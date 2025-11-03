#include "Student.h"

// std::expected<Student, std::string> Student::getStudentFromKeyboard(std::string message, int maxAttempts) {
//     std::cout << message << '\n';
//     int attempted = 0;
//     while (attempted < maxAttempts) {
//         std::cout <<  std::format("     (Còn {0} lần) Nhập dữ liệu yêu cầu:\n", maxAttempts - attempted);
//         Student temp;
//         if (!(std::cin >> temp) ) {
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             attempted += 1;
//         } else {
//             std::cout << '\n';
//             return temp;
//         }
//     }
//     return std::unexpected("Quá số lần nhập dữ liệu");
// }

void Student::printInfo() {
    std::cout << "MSSV: " << this->_id << '\n';
    std::cout << "Họ và tên: " << this->_name << '\n';
    std::cout << "GPA: " << this->_gpa << '\n';
}


std::istream& operator>>(std::istream& is, Student& sv) {
    std::cout << "      Nhập mã số sinh viên: ";
    is.ignore();
    std::string temp; getline(is, temp);
    sv.setid(temp);

    std::cout << "      Nhập họ và tên của sinh viên: ";
    std::getline(is, temp);
    sv.setName(temp);
    
    std::cout << "      Nhập GPA của sinh viên: ";
    float tempGPA;
    if (!(is >> tempGPA)) {
        return is;
    }
    sv.setGPA(tempGPA);

    return is;
}

std::string Student::id() const { return _id; }
std::string Student::name() const { return _name; }
float Student::gpa() const { return _gpa; }

void Student::setid(const std::string &input) {
    _id = input;
}

void Student::setName(const std::string &input) {
    _name = input;
}

void Student::setGPA(const float &gpa) {
    if (gpa < 0) {
        _gpa = 0;
    } else if (gpa > 10) {
        _gpa = 10;
    }
    else _gpa = gpa;
}