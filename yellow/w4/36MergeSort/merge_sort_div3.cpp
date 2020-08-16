#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt _beg, RandomIt _end) {
    if (auto size = distance(_beg, _end); size > 1) {
        vector<typename RandomIt::value_type> elements(_beg, _end);
        auto mid1 = next(begin(elements), size / 3) + (size % 3 != 0);
        auto mid2 = next(mid1, size / 3);

        MergeSort(begin(elements), mid1);
        MergeSort(mid1, mid2);
        MergeSort(mid2, end(elements));

        vector<typename RandomIt::value_type> tmp;
        merge(begin(elements), mid1, mid1, mid2, back_inserter(tmp));
        merge(begin(tmp), end(tmp), mid2, end(elements), _beg);
    }
}

// #include <chrono>
// int main() {
//     srand(time(nullptr));
//     const size_t size = 2354782;
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
