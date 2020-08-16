#include <iostream>

int Factorial(int a) {
    return a > 0 ? a * Factorial(a - 1) : 1;
}

int main() {
    int a;
    std::cin >> a;
    std::cout << Factorial(a);
}
