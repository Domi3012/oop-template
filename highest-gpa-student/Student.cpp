#include "Student.h"

int Student::findMaxGPAStudent(std::vector<Student> vec) {
    float maxGPA = -INT_MAX;
    int resIndex = -1;

    for (int i = 0; i < vec.size(); i++) {
        if (maxGPA < vec[i]._gpa) {
            maxGPA = vec[i]._gpa;
            resIndex = i;
        }
    }
    
    return resIndex;
}

std::expected<Student, std::string> Student::getStudentFromKeyboard(std::string message, int maxAttempts) {
    std::cout << message << '\n';
    int attempted = 0;
    while (attempted < maxAttempts) {
        std::cout <<  std::format("     (Còn {0} lần) Nhập dữ liệu yêu cầu:\n", maxAttempts - attempted);
        Student temp;
        if (!(std::cin >> temp) ) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            attempted += 1;
        } else {
            std::cout << '\n';
            return temp;
        }
    }
    return std::unexpected("Quá số lần nhập dữ liệu");
}

void Student::printInfo() {
    std::cout << "MSSV: " << this->_id << '\n';
    std::cout << "Họ và tên: " << this->_name << '\n';
    std::cout << "GPA: " << this->_gpa << '\n';
}


std::istream& operator>>(std::istream& is, Student& sv) {
    std::cout << "      Nhập mã số sinh viên: ";
    if (!(is >> sv._id)) {
        return is;
    }

    std::cout << "      Nhập họ và tên của sinh viên: ";
    is.ignore();
    std::getline(is, sv._name);
    
    std::cout << "      Nhập GPA của sinh viên: ";
    if (!(is >> sv._gpa)) {
        return is;
    }
    
    return is;
}
