#include <iostream>
#include <string>
#include <map>
using std::cin, std::cout, std::endl, std::map, std::string;

map<char, int> parse(string &word) {
    map<char, int> m;
    for (auto i : word)
        ++m[i];
    return m;
}

int main() {
    int n;
    cin >> n;
    string w1, w2;

    for (int i = 0; i < n; ++i) {
        cin >> w1 >> w2;
        cout << (parse(w1) == parse(w2) ? "YES" : "NO") << endl;
    }
}
