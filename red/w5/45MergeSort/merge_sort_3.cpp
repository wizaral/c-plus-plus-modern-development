#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt _beg, RandomIt _end) {
    if (auto size = distance(_beg, _end); size > 1) {
        vector<typename RandomIt::value_type> elements(
            make_move_iterator(_beg), make_move_iterator(_end));

        auto mid1 = next(elements.begin(), size / 3) + (size % 3 != 0);
        auto mid2 = next(mid1, size / 3);

        MergeSort(elements.begin(), mid1);
        MergeSort(mid1, mid2);
        MergeSort(mid2, elements.end());

        vector<typename RandomIt::value_type> tmp;
        merge(make_move_iterator(elements.begin()), make_move_iterator(mid1),
            make_move_iterator(mid1), make_move_iterator(mid2),
            back_inserter(tmp));
        merge(make_move_iterator(tmp.begin()), make_move_iterator(tmp.end()),
            make_move_iterator(mid2), make_move_iterator(elements.end()),
            _beg);
    }
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}
