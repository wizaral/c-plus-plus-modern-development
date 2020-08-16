#include <iostream>
#include <list>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::list<int> row;
    std::vector<std::list<int>::iterator> iters(100000, row.end());

    for (int prev, next; n; --n) {
        std::cin >> prev >> next;
        iters[prev] = row.insert(iters[next], prev);
    }
    for (auto athlet : row)
        std::cout << athlet << ' ';
    std::cout << '\n';
}
