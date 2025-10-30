#include <iostream>
#include <vector>
#include <expected>
#include <format>
#include <climits>


using Condition = bool (*)(int);
// Functions' declarations
std::expected<int, std::string> getIntFromKeyboard(std::string message, Condition c, int maxAttempts);
int calcEvenSum(const std::vector<int> &vec);
void mainUseCase();

class Student {
public:
    std::string _id;
    std::string _name;
    float _gpa;

    static int findMaxGPAStudent(std::vector<Student> vec) {
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

    void printInfo() {
        std::cout << "Họ và tên: " << this->_name << '\n';
        std::cout << "MSSV: " << this->_id << '\n';
        std::cout << "GPA: " << this->_gpa << '\n';
    }
};

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

int main() {
    std::cout << "Chương trình nhập danh sách sinh viên và tìm sinh viên có GPA cao nhất.\n\n\n";

    mainUseCase();

    std::cout << "Chương trình đang thoát...";
    std::cin.get();
    std::cin.get();
    return 0;
}



std::expected<int, std::string> getIntFromKeyboard(std::string message, Condition c, int maxAttempts) {
    std::cout << message << '\n';
    int attempted = 0;
    while (attempted < maxAttempts) {
        std::cout <<  std::format("     (Còn {0} lần) Nhập dữ liệu yêu cầu: ", maxAttempts - attempted);
        int temp;
        if (!(std::cin >> temp) || !c(temp)) {
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

std::expected<Student, std::string> getStudentFromKeyboard(std::string message, int maxAttempts) {
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

int calcEvenSum (const std::vector<int> &vec) {
    int res = 0;
    for (int x: vec) {
        if (x % 2 == 0) res += x;
    }
    return res;
}

void mainUseCase() {
    Condition c = [](int x) { return x >= 2 && x <= 10; };
    auto result = getIntFromKeyboard("Hãy nhập số lượng sinh viên (giá trị từ  2 - 10): ", c, 5);
    if (!result) {
        std::cout << "Error: " << result.error() << '\n';
        return;
    }
    int n = result.value();

    std::vector<Student> sv(n);

    for (int i = 0; i < n; i++) {
        auto result = getStudentFromKeyboard(
            std::format("Hãy nhập sinh viên thứ {0}: ", i),
            3
        );
        if (result) {
            sv[i] = result.value();
        } else {
            std::cout << "Error: " << result.error() << '\n';
            return; 
        }
    }

    int indexMax = Student::findMaxGPAStudent(sv);
    std::cout << "Sinh viên có GPA cao nhất là:\n";
    sv[indexMax].printInfo();

}
