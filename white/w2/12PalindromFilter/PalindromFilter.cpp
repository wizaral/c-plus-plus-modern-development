#include <string>
#include <vector>

bool IsPalindrom(const std::string &str) {
    int i = 0, j = str.size() - 1;
    for (; i < j && str[i] == str[j]; ++i, --j);
    return i >= j;
}

std::vector<std::string> PalindromFilter(std::vector<std::string> words, int minLength) {
    std::vector<std::string> result;

    for (const auto &w : words)
        if (w.size() >= minLength && IsPalindrom(w))
            result.push_back(w);
    return result;
}
