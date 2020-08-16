#include <iostream>
using std::cin, std::cout, std::endl;

int main() {
    uint64_t sum = 0, w, h, d;
    int size, density;
    cin >> size >> density;

    for (int i = 0; i < size; ++i, sum += w * h * d)
        cin >> w >> h >> d;
    cout << sum * density << endl;
}
