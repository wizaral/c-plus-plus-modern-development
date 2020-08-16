#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    return {lower_bound(range_begin, range_end, string(1, prefix)),
            upper_bound(range_begin, range_end, string(1, prefix + 1))};
}

int main() {
    const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

    const auto m_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    cout << (m_result.first - begin(sorted_strings)) << " " << (m_result.second - begin(sorted_strings)) << endl;
    for (auto it = m_result.first; it != m_result.second; ++it)
        cout << *it << " ";
    cout << endl;

    const auto p_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " << (p_result.second - begin(sorted_strings)) << endl;

    const auto z_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " << (z_result.second - begin(sorted_strings)) << endl;
}
