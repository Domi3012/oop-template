#ifndef UI_H
#define UI_H

#include <iostream>
#include <expected>


namespace ui {
    std::expected<int, std::string> getIntInRangeWithRetry(const std::string& message, int maxAttempts, int from, int to);

    template <class T>
    std::expected<T, std::string> getItemWithRetry(std::string& message, int maxAttempts) {
        std::cout << message << '\n';
        int attempted = 0;
        while (attempted < maxAttempts) {
            std::cout <<  std::format("     (Còn {0} lần) Nhập số được yêu cầu: ", maxAttempts - attempted);
            T temp;
            if (!(std::cin >> temp)) {
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
}

#endif