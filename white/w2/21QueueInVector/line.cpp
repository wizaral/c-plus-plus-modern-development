#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl;
using std::function, std::map, std::string, std::vector;

void come(vector<int> &people) {
    int count;
    cin >> count;
    people.resize(people.size() + count);
}

void quiet(vector<int> &people) {
    int index;
    cin >> index;
    people[index] = false;
}

void worry(vector<int> &people) {
    int index;
    cin >> index;
    people[index] = true;
}

void count(vector<int> &people) {
    cout << std::accumulate(people.begin(), people.end(), 0) << endl;
}

int main() {
    string command;
    vector<int> people;
    map<string, function<void(vector<int> &)>> commands =
        {{"COME", come}, {"QUIET", quiet}, {"WORRY", worry}, {"WORRY_COUNT", count}};

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        cin >> command;
        commands[command](people);
    }
}
