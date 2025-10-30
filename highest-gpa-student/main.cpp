#include <iostream>
#include <vector>
#include <expected>
#include <format>
#include <climits>

#include "Student.h"

using Condition = bool (*)(int);
// Functions' declarations
std::expected<int, std::string> getIntFromKeyboard(std::string message, Condition c, int maxAttempts);
void mainUseCase();


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
        auto result = Student::getStudentFromKeyboard(
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
