#include "UI.h"

std::expected<int, std::string> ui::getIntInRangeWithRetry(const std::string& message, int maxAttempts, int from, int to) {
    std::cout << message << '\n';
    int attempted = 0;
    while (attempted < maxAttempts) {
        std::cout <<  std::format("     (Còn {0} lần) Nhập số được yêu cầu: ", maxAttempts - attempted);
        int temp;
        if (!(std::cin >> temp) || !(temp >= from && temp <= to)) {
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

// TO DO: IMPLEMENT 2 HAM TRONG UI, VIET HAM MAIN, TACH USE CASE