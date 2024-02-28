#include <iostream>
#include "bin_tree.hpp"
#include "avl_tree.hpp"

int main() {
    avl_tree<int> s;
    std::string command;
    while (true) {
        std::cin >> command;
        if (command == "exit") {
            break;
        } else if (command == "insert") {
            int n;
            std::cin >> n;
            s.insert(n);
        } else if (command == "erase") {
            int n;
            std::cin >> n;
            s.erase(n);
        } else if (command == "contains") {
            int n;
            std::cin >> n;
            std::cout << s.contains(n) << std::endl;
        } else if (command == "print") {
            for (auto elem : s) {
                std::cout << elem << ' ';
            }
            std::cout << std::endl;
        } else {
            std::cout << "...";
        }
    }
}