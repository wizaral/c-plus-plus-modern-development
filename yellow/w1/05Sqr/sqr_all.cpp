#include <iostream>
#include <map>
#include <vector>
using std::cin, std::cout, std::endl;
using std::map, std::pair, std::vector;

template <class T>
T Sqr(const T &p) {
    return p * p;
}

template <class T, class U>
pair<T, U> Sqr(const pair<T, U> &p) {
    return {Sqr(p.first), Sqr(p.second)};
}

template <class T>
vector<T> Sqr(const vector<T> &v) {
    vector<T> container(v);
    for (auto &i : container)
        i = Sqr(i);
    return container;
}

template <class T, class U>
map<T, U> Sqr(const map<T, U> &m) {
    map<T, U> container(m);
    for (auto &i : container)
        i.second = Sqr(i.second);
    return container;
}

int main() {
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
        cout << ' ' << x;
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}},
    };
    cout << "map of pairs:" << endl;
    for (const auto &[key, value] : Sqr(map_of_pairs))
        cout << key << ' ' << value.first << ' ' << value.second << endl;
}
