#include <iostream>
using std::cin, std::cout;

int main() {
    int a, b;
    cin >> a >> b;

    for (int i = a + (a & 1); i <= b; i += 2)
        cout << i << ' ';
}
