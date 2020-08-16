#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    int count = 0;

    for (int i = 0, size = str.size(); i < size && count < 2; ++i)
        if (count += str[i] == 'f'; count == 2)
            std::cout << i;

    if (count < 2)
        std::cout << -((count == 0) + 1);
}
