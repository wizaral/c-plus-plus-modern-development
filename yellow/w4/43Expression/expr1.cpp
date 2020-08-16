#include <iostream>
#include <string>
#include <deque>
using std::cin, std::cout, std::endl;
using std::deque, std::string, std::to_string;

int main() {
    char c;
    int n, ops;
    if (cin >> n >> ops; ops) {
        deque<string> expr{to_string(n)};
        string str(3, ' ');

        for (int i = 0; i < ops; ++i) {
            expr.push_front("(");
            expr.push_back(")");
            cin >> c >> n;
            str[1] = c;
            expr.push_back(str);
            expr.push_back(to_string(n));
        }

        for (const auto &i : expr)
            cout << i;
    } else
        cout << n;
}
