#include <fstream>
#include <iostream>
#include <iomanip>

int main() {
    if (std::ifstream is("input.txt"); is) {
        std::cout << std::fixed << std::setprecision(3);
        for (double d; is >> d; std::cout << d << '\n');
    }
}
