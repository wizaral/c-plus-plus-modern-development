#include <iostream>

using std::cin, std::cout;

int main() {
    int a, b;
    cin >> a >> b;

    if (b == 0)
        cout << "Impossible";
    else
        cout << a / b;
}
