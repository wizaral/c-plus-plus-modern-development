#include <algorithm>
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::vector, std::pair;
using ll = long long;

pair<vector<int>, ll> init() {
    int n;
    cin >> n;
    pair<vector<int>, ll> p{vector<int>(n), 0LL};

    for (auto &i : p.first) {
        cin >> i;
        p.second += i;
    }
    return p;
}

void print(vector<int> &v, ll mid, int count) {
    cout << count << endl;
    for (int i = 0, size = v.size(); i < size; ++i)
        if (v[i] > mid)
            if (cout << i; --count)
                cout << ' ';
}

int main() {
    if (pair<vector<int>, double> p = move(init()); !p.first.empty()) {
        ll mid = p.second / p.first.size();
        int count = std::count_if(p.first.begin(), p.first.end(), [mid](int &i) { return i > mid; });
        print(p.first, mid, count);
    }
}
