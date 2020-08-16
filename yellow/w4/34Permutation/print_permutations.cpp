#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
using namespace std;

void print(const string &s) {
    ostream_iterator<char> osi(cout, " ");
    copy(cbegin(s), --cend(s), osi);
    cout << s.back() << endl;
}

int main() {
    int N;
    cin >> N;
    ostream::sync_with_stdio(false);

    string s(N, '\0');
    iota(s.rbegin(), s.rend(), '1');
    for (print(s); prev_permutation(begin(s), end(s)); print(s));
}
