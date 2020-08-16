#include <iostream>
#include <string>
#include <deque>
using std::cin, std::cout, std::endl;
using std::deque, std::string, std::to_string;

int main() {
    char c;
    int n, ops, type = 1;
    if (cin >> n >> ops; ops) {
        deque<string> expr{to_string(n)};
        string str(3, ' ');

        for (int i = 0; i < ops; ++i) {
            cin >> c >> n;

            if (type < (c == '*' || c == '/')) {
                expr.push_front("(");
                expr.push_back(")");
            }

            str[1] = c;
            expr.push_back(str);
            expr.push_back(to_string(n));
            type = c == '*' || c == '/';
        }

        for (const auto &i : expr)
            cout << i;
    } else
        cout << n;
}
