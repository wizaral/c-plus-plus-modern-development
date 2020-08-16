#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;

#define merge_push(v, it)           \
    do {                            \
        (v).push_back(move(*(it))); \
        ++(it);                     \
    } while (0)

#define merge_cmp(v, lhs, rhs)    \
    do {                          \
        if (*(lhs) < *(rhs))      \
            merge_push((v), lhs); \
        else                      \
            merge_push((v), rhs); \
    } while (0)

template <typename RandomIt>
void Merge(RandomIt _beg, RandomIt _mid, RandomIt _end) {
    vector<typename RandomIt::value_type> v;
    auto lhs = _beg, rhs = _mid;
    v.reserve(distance(_beg, _end));

    while (lhs != _mid && rhs != _end)
        merge_cmp(v, lhs, rhs);
    v.insert(end(v), lhs, _mid);
    v.insert(end(v), rhs, _end);
    move(begin(v), end(v), _beg);
}

template <typename RandomIt>
void MergeSort(RandomIt _beg, RandomIt _end) {
    if (auto size = distance(_beg, _end); size > 1) {
        auto mid = next(_beg, size / 2);
        MergeSort(_beg, mid);
        MergeSort(mid, _end);
        Merge(_beg, mid, _end);
    }
}

// int main() {
//     srand(time(nullptr));
//     const size_t size = 100;
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
