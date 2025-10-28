#include <iostream>
#include <vector>
#include <expected>
#include <format>
#include <climits>

using Condition = bool (*)(int);

std::expected<int, std::string> getIntFromKeyboard(std::string message, Condition c, int maxAttempts);

int calcEvenSum(const std::vector<int> &vec);

void mainUseCase();

int main() {
    std::cout << "Chương trình nhập mảng và tính các phần tử chẵn của mảng.\n\n\n";
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

int calcEvenSum (const std::vector<int> &vec) {
    int res = 0;
    for (int x: vec) {
        if (x % 2 == 0) res += x;
    }
    return res;
}

void mainUseCase() {
    Condition c = [](int x) { return x >= 2 && x <= 10; };
    auto result = getIntFromKeyboard("Hãy nhập số lượng phần tử của mảng (giá trị từ  2 - 10): ", c, 5);
    if (!result) {
        std::cout << "Error: " << result.error() << '\n';
        return;
    }
    int n = result.value();

    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        c = [](int x) { return x >= 10 && x <= 100; };
        result = getIntFromKeyboard(
            std::format("Hãy nhập phần tử thứ {0} của mảng (giá trị từ 10 - 100): ", i),
            c, 3
        );
        if (!result) {
            std::cout << "Error: " << result.error() << '\n';
            return;
        }
        vec[i] = result.value();
    }
    std::cout << "Tổng các số chẵn của mảng là: " << calcEvenSum(vec) << '\n';
}
