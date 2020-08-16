#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::map, std::string, std::vector;

vector<string> get_stops() {
    int count;
    cin >> count;
    vector<string> v(count);

    for (int j = 0; j < count; ++j)
        cin >> v[j];
    return v;
}

int main() {
    map<vector<string>, int> buses;

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        if (vector<string> v = get_stops(); buses.count(v)) {
            cout << "Already exists for " << (*buses.find(v)).second << endl;
        } else {
            int number = buses.size() + 1;
            cout << "New bus " << (buses[v] = number) << endl;
        }
    }
}
