#include "mainUseCase.h"
#include "../bus/Algorithms.h"
#include "../dto/Student.h"
#include "../lib/DynamicVector.h"
#include "../lib/Reduce.h"
#include "../ui/UI.h"
#include "../useCase/mainUseCase.h"
#include <format>

void greet(std::string message) {
    std::cout << message << '\n';
}

void bye() {
    std::cout << "Chương trình đang thoát...";
    std::cin.get();
    std::cin.get();
}

void UseCase::executeEx1() {
    greet("CHƯƠNG TRÌNH TÍNH TỔNG CÁC SỐ CHẴN CỦA MẢNG.");

    auto result = ui::getIntInRangeWithRetry("Hãy nhập số lượng phần tử của mảng (số nguyên có giá trị 2 - 10):", 5, 2, 10);
    if (!result) {
        std::cout << "Error: " << result.error() << '\n';
        return;
    }
    
    int n = result.value();
    DynamicVector<int> vec;
    for (int i = 0; i < n; i++) {
        result = ui::getIntInRangeWithRetry(
            std::format("Hãy nhập phần tử thứ {0} của mảng (số nguyên có giá trị 10 - 100): ", i),
            3, 10, 100
        );
        if (!result) {
            std::cout << "Error: " << result.error() << '\n';
            return;
        }
        vec.push_back(result.value());
    }

    int res = reduce(vec, 0, bus::addIfEven);
    std::cout << "Tổng các số chẵn của mảng là: " << res << '\n';

    bye();
}

void UseCase::executeEx2() {
    greet("CHƯƠNG TRÌNH NHẬP VÀ TÌM SINH VIÊN CÓ ĐIỂM CAO NHẤT.");
    auto result = ui::getIntInRangeWithRetry("Hãy nhập số lượng sinh viên (số nguyên có giá trị 2 - 10):", 5, 2, 10);
    if (!result) {
        std::cout << "Error: " << result.error() << '\n';
        return;
    }
    
    int n = result.value();
    DynamicVector<Student> vec;
    for (int i = 0; i < n; i++) {
        std::string message = std::format("Hãy nhập sinh viên thứ {0}:\n", i);
        auto resu = ui::getItemWithRetry<Student>(message, 3);
        if (!resu) {
            std::cout << "Error: " << result.error() << '\n';
            return;
        }
        vec.push_back(resu.value());
    }

    Student res = reduce(vec, vec[0].value(), bus::findMaxGPA);
    std::cout << "Sinh viên với GPA cao nhất là:\n" << res << '\n';

    bye();
}

void UseCase::execute() {
    executeEx1();
    executeEx2();
}