#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

template <class T>
vector<T> FindGreaterElements(const set<T> &elements, const T &border) {
    return {upper_bound(begin(elements), end(elements), border), end(elements)};
}

int main() {
    for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5))
        cout << x << " ";
    cout << endl;

    string to_find = "Python";
    cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
    return 0;
}
