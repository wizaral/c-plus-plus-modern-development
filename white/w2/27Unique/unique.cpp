#include <iostream>
#include <set>
#include <string>
using std::cin, std::cout, std::endl;
using std::set, std::string;

int main() {
    int count;
    string str;
    cin >> count;
    set<string> strs;

    for (int i = 0; i < count; ++i) {
        cin >> str;
        strs.insert(move(str));
    }
    cout << strs.size() << endl;
}
