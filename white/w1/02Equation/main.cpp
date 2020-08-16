#include <iostream>
#include <cmath>

int main() {
    if (double a, b, c; std::cin >> a >> b >> c, a != 0) {
        if (double d = b * b - 4 * a * c; d > 0)
            std::cout << (-b + std::sqrt(d)) / (2 * a) << ' ' << (-b - std::sqrt(d)) / (2 * a);
        else if (d == 0)
            std::cout << -b / (2 * a);
    } else if (b != 0)
        std::cout << -(c / b);
}
