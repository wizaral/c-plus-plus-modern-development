#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <class C>
struct lc_t : public std::char_traits<C> {
    static bool eq(C c1, C c2) {
        return std::tolower(c1) == std::tolower(c2);
    }
    static bool lt(C c1, C c2) {
        return std::tolower(c1) < std::tolower(c2);
    }
    static int compare(const C *s1, const C *s2, size_t n) {
        for (C c1, c2; n--; ++s1, ++s2)
            if (c1 = std::tolower(*s1), c2 = std::tolower(*s2); c1 != c2)
                return c1 - c2;
        return 0;
    }
};

using string = std::basic_string<char, lc_t<char>>;
template <class C, class Traits, class C2>
std::basic_ostream<C, Traits>& operator<<(std::basic_ostream<C, Traits> &os,
    const std::basic_string<C2, lc_t<C2>> &str) {
    return os.write(str.data(), str.size());
}

template <class C, class Traits, class C2>
std::basic_istream<C, Traits>& operator>>(std::basic_istream<C, Traits> &is,
    std::basic_string<C2, lc_t<C2>> &str) {
    char c;
    str.erase();

    for (is.read(&c, 1); !is.eof() && std::isspace(c, is.getloc()); is.read(&c, 1));
    if (!is.eof() && std::isspace(c, is.getloc()) == false)
        str.append(1, c);

    for (size_t i = 0, N = is.width() > 0 ? is.width() : str.max_size(); i < N; ++i) {
        if (is.read(&c, 1); is.eof() || std::isspace(c, is.getloc()))
            break;
        str.append(1, c);
    }
    is.width(0);
    return is;
}

std::vector<string> init() {
    int size;
    std::cin >> size;
    std::vector<string> v(size);
    for (auto &i : v)
        std::cin >> i;
    return v;
}

void print(const std::vector<string> &v) {
    for (const auto &i : v)
        std::cout << i << ' ';
}

int main() {
    std::vector<string> v(move(init()));
    std::sort(begin(v), end(v));
    print(v);
}
