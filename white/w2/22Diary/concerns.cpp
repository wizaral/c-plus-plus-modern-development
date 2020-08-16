#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

using std::array, std::map, std::vector;
using std::cin, std::cout, std::endl;
using std::function, std::string;

struct Dairy;

void add(Dairy &dairy);
void next(Dairy &dairy);
void dump(Dairy &dairy);

struct Dairy {
    inline static const array<int, 12> calendar {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int current_month = 0;
    map<string, function<void(Dairy &)>> commands {{"ADD", add}, {"NEXT", next}, {"DUMP", dump}};
    vector<vector<string>> tasks = vector<vector<string>>(calendar[current_month]);

    Dairy() = default;

    void execute(string &command) {
        commands[command](*this);
    }
};

void add(Dairy &dairy) {
    int i;
    string str;
    cin >> i >> str;
    dairy.tasks[i - 1].emplace_back(std::move(str));
}

void next(Dairy &dairy) {
    int current_days = dairy.calendar[dairy.current_month];
    int next_month_days = dairy.calendar[(++dairy.current_month %= 12)];

    if (next_month_days < current_days) {
        vector<string> &last_day = dairy.tasks[next_month_days - 1];
        for (int day = next_month_days; day < current_days; ++day)
            last_day.insert(last_day.end(), dairy.tasks[day].begin(), dairy.tasks[day].end());
    }
    dairy.tasks.resize(next_month_days);
}

void dump(Dairy &dairy) {
    int i;
    cin >> i;
    cout << dairy.tasks[--i].size();

    for (auto &t : dairy.tasks[i])
        cout << ' ' << t;
    cout << endl;
}

int main() {
    Dairy dairy;
    string command;

    int operations;
    cin >> operations;
    for (int i = 0; i < operations; ++i) {
        cin >> command;
        dairy.execute(command);
    }
}
