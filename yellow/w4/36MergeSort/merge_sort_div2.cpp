#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt _beg, RandomIt _end) {
    if (auto size = distance(_beg, _end); size > 1) {
        vector<typename RandomIt::value_type> v(_beg, _end);
        auto mid = next(begin(v), size / 2);

        MergeSort(begin(v), mid);
        MergeSort(mid, end(v));
        merge(begin(v), mid, mid, end(v), _beg);
    }
}

// #include <chrono>
// int main() {
//     srand(time(nullptr));
//     const size_t size = 128;
//     vector<int> v;
//     v.reserve(size);

//     for (size_t i = 0; i < size; ++i)
//         v.push_back(rand());

//     chrono::time_point<chrono::system_clock> start, stop;
//     start = chrono::system_clock::now();
//     MergeSort(begin(v), end(v));
//     stop = chrono::system_clock::now();
//     cout << boolalpha << chrono::duration_cast<chrono::seconds>(stop - start).count() << " sec; sorted: " << is_sorted(begin(v), end(v)) << endl;
//     // for (int x : v)
//     //     cout << x << " ";
//     // cout << endl;
// }
