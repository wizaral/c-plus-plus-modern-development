#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::map, std::pair, std::string, std::vector;

void new_bus(pair<map<string, vector<string>>, map<string, vector<string>>> &data) {
    int count;
    string bus, stop;
    auto &[buses, stops] = data;
    cin >> bus >> count;

    for (int i = 0; i < count; ++i) {
        cin >> stop;
        stops[stop].push_back(bus);
        buses[bus].push_back(stop);
    }
}

void buses_for_stop(map<string, vector<string>> &stops) {
    string stop;

    if (cin >> stop; stops.count(stop)) {
        auto it = stops[stop].begin(), end = stops[stop].end();
        for (cout << *it, ++it; it != end; cout << *it, ++it)
            cout << ' ';
        cout << endl;
    } else
        cout << "No stop" << endl;
}

void stops_for_bus(pair<map<string, vector<string>>, map<string, vector<string>>> &data) {
    string bus;
    auto &[buses, stops] = data;

    if (cin >> bus; buses.count(bus)) {
        for (const auto &s : buses[bus]) {
            if (cout << "Stop " << s << ':'; stops[s].size() > 1) {
                for (const auto &b : stops[s]) {
                    if (b != bus)
                        cout << ' ' << b;
                }
                cout << endl;
            } else
                cout << " no interchange" << endl;
        }
    } else
        cout << "No bus" << endl;
}

void all_buses(map<string, vector<string>> &buses) {
    if (buses.size()) {
        for (const auto &[bus, stops] : buses) {
            cout << "Bus " << bus << ":";
            for (const auto &s : stops)
                cout << ' ' << s;
            cout << endl;
        }
    } else
        cout << "No buses" << endl;
}

int main() {
    string command;
    pair<map<string, vector<string>>, map<string, vector<string>>> data;

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        if (cin >> command; command == "NEW_BUS")
            new_bus(data);
        else if (command == "BUSES_FOR_STOP")
            buses_for_stop(data.second);
        else if (command == "STOPS_FOR_BUS")
            stops_for_bus(data);
        else if (command == "ALL_BUSES")
            all_buses(data.first);
    }
}
