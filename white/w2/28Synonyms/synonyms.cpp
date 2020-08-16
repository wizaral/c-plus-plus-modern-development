#include <iostream>
#include <map>
#include <string>
#include <set>

using std::cin, std::cout, std::endl;
using std::map, std::set, std::string;

void add(map<string, set<string>> &data) {
    string word1, word2;
    cin >> word1 >> word2;

    data[word1].insert(word2);
    data[word2].insert(word1);
}

void count(map<string, set<string>> &data) {
    string word;
    cin >> word;

    if (auto it = data.find(word); it != data.end())
        cout << (*it).second.size() << endl;
    else
        cout << '0' << endl;
}

void check(map<string, set<string>> &data) {
    string word1, word2;
    cin >> word1 >> word2;
    cout << (data[word1].count(word2) ? "YES" : "NO") << endl;
}

int main() {
    string command;
    map<string, set<string>> data;

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        if (cin >> command; command == "ADD")
            add(data);
        else if (command == "COUNT")
            count(data);
        else if (command == "CHECK")
            check(data);
    }
}
