#include <algorithm>
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;

std::vector<int> init() {
    int size;
    cin >> size;
    std::vector<int> v(size);
    for (auto &i : v)
        cin >> i;
    return v;
}

void print(const std::vector<int> &v) {
    for (const auto &i : v)
        cout << i << ' ';
}

int main() {
    std::vector<int> v(std::move(init()));
    std::sort(begin(v), end(v), [](int &i1, int &i2) { return abs(i1) < abs(i2); });
    print(v);
}
