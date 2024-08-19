#include <iostream>
#include <optional>

int main() {
    std::optional<int> opt = 42;
    if (opt) {
        std::cout << "C++17 is supported." << std::endl;
    }
    return 0;
}
