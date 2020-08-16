#include <iostream>
#include <map>
#include <string>
#include <set>

using std::cin, std::cout, std::endl;
using std::map, std::set, std::string;

set<string> get_stops() {
    int count;
    cin >> count;
    string str;
    set<string> s;

    for (int j = 0; j < count; ++j) {
        cin >> str;
        s.insert(str);
    }
    return s;
}

int main() {
    map<set<string>, int> buses;

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        if (set<string> s = move(get_stops()); buses.count(s)) {
            cout << "Already exists for " << (*buses.find(s)).second << endl;
        } else {
            int number = buses.size() + 1;
            cout << "New bus " << (buses[s] = number) << endl;
        }
    }
}
