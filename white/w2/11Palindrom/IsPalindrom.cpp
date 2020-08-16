#include <iostream>
#include <string>

bool IsPalindrom(std::string &str) {
    int i = 0, j = str.size() - 1;
    for (; i < j && str[i] == str[j]; ++i, --j);
    return i >= j;
}

int main() {
    std::string str;
    std::cin >> str;
    std::cout << IsPalindrom(str);
}
