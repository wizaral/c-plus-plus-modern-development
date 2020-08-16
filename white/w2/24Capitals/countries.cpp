#include <iostream>
#include <map>
#include <string>

using std::cin, std::cout, std::endl;
using std::map, std::string;

void change(map<string, string> &data) {
    string country, capital;
    cin >> country >> capital;

    if (data.count(country) == 0) {
        cout << "Introduce new country " << country << " with capital " << capital << endl;
        data[country] = move(capital);
    } else if (auto it = data.find(country); (*it).second != capital) {
        cout << "Country " << country << " has changed its capital from " << (*it).second << " to " << capital << endl;
        data[country] = move(capital);
    } else {
        cout << "Country " << country << " hasn't changed its capital" << endl;
    }
}

void rename(map<string, string> &data) {
    string old_name, new_name;
    cin >> old_name >> new_name;

    if (data.count(old_name) && !data.count(new_name) && old_name != new_name) {
        cout << "Country " << old_name << " with capital " << data[old_name] << " has been renamed to " << new_name << endl;
        auto old = move(data.extract(old_name));
        old.key() = move(new_name);
        data.insert(move(old));
    } else
        cout << "Incorrect rename, skip" << endl;
}

void about(map<string, string> &data) {
    string country;
    cin >> country;

    cout << "Country " << country;
    if (data.find(country) != data.end())
        cout << " has capital " << data[country] << endl;
    else
        cout << " doesn't exist" << endl;
}

void dump(map<string, string> &data) {
    if (data.size()) {
        for (const auto &[country, capital] : data)
            cout << country << '/' << capital << ' ';
        cout << endl;
    } else
        cout << "There are no countries in the world" << endl;
}

int main() {
    string command;
    map<string, string> data;

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        if (cin >> command; command == "ABOUT")
            about(data);
        else if (command == "DUMP")
            dump(data);
        else if (command == "CHANGE_CAPITAL")
            change(data);
        else if (command == "RENAME")
            rename(data);
    }
}
