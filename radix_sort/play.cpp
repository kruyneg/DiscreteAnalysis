#include <iostream>
#include "radix_sort.hpp"

int main() {
    while(true) {
        std::cout << "Enter size of vector or \"exit\":";
        std::cout.flush();
        std::string input;
        std::cin >> input;

        size_t n;
        if (input == "exit") {
            break;
        }
        else {
            n = std::stoi(input);
        }
        std::vector<long long> v(n);
        std::cout << "Enter vector:" << std::endl;
        for (size_t i = 0; i < n; ++i) {
            std::cin >> v[i];
        }

        radix_sort(v);

        for (auto& elem : v) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
}