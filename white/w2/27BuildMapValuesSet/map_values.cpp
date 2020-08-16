#include <iostream>
#include <map>
#include <set>
#include <string>
using std::cin, std::cout, std::endl;
using std::map, std::set, std::string;

set<string> BuildMapValuesSet(const map<int, string> &m) {
    set<string> s;
    for (auto &[key, value] : m)
        s.insert(value);
    return s;
}

int main() {
    set<string> values = BuildMapValuesSet({{1, "odd"}, {2, "even"}, {3, "odd"}, {4, "even"}, {5, "odd"}});
    for (const string &value : values)
        cout << value << endl;
}
