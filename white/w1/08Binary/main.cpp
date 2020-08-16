#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    if (n != 0) {
        std::string str(32, 48);
        for (int i = 0; i < 32; ++i, n <<= 1)
            str[i] += ((n & 2147483648) != 0);
        std::cout << (str.erase(0, str.find(49)), str);
    } else
        std::cout << "0";
}
