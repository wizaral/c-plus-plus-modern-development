#include <algorithm>
#include <iostream>
#include <vector>
using std::cin, std::cout, std::endl, std::pair, std::vector;

pair<vector<int>, double> init() {
    int n;
    cin >> n;
    pair<vector<int>, double> p{vector<int>(n), 0.0};

    for (auto &i : p.first) {
        cin >> i;
        p.second += i;
    }
    return p;
}

void print(vector<int> &v, double mid) {
    for (int i = 0, size = v.size(); i < size; ++i)
        if (v[i] > mid)
            cout << i << ' ';
}

int main() {
    if (pair<vector<int>, double> p = std::move(init()); !p.first.empty()) {
        double mid = p.second / p.first.size();
        int count = std::count_if(p.first.begin(), p.first.end(), [mid](int &i) { return i > mid; });
        cout << count << endl;
        print(p.first, mid);
    }
}
