#include <iostream>
#include <string>

int main() {
    std::string x, y, z;
    std::cin >> x >> y >> z;

    if (x <= y && x <= z)
        std::cout << x;
    else if (y <= x && y <= z)
        std::cout << y;
    else
        std::cout << z;
}
