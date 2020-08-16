#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <class T>
void Swap(T *first, T *second) {
    T temp = move(*first);
    *first = move(*second);
    *second = move(temp);
}

template <class T>
void SortPointers(vector<T *> &pointers) {
    sort(pointers.begin(), pointers.end(), [](T *lhs, T *rhs) {
        return *lhs < *rhs;
    });
}

template <class T>
void ReversedCopy(T *source, size_t count, T *destination) {
    auto src_end = source + count;
    auto dst_end = destination + count;

    if (destination >= src_end || dst_end <= source) {
        reverse_copy(source, src_end, destination);
    } else if (destination > source) {
        for (size_t i = 0; source + i < destination; ++i)
            *(dst_end - i - 1) = *(source + i);
        reverse(destination, src_end);
    } else {
        for (size_t i = 0; src_end - i - 1 >= dst_end; ++i)
            *(destination + i) = *(src_end - i - 1);
        reverse(source, dst_end);
    }
}

void TestSwap() {
    int a = 1;
    int b = 2;
    Swap(&a, &b);
    ASSERT_EQUAL(a, 2);
    ASSERT_EQUAL(b, 1);

    string h = "world";
    string w = "hello";
    Swap(&h, &w);
    ASSERT_EQUAL(h, "hello");
    ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
    int one = 1;
    int two = 2;
    int three = 3;

    vector<int *> pointers;
    pointers.push_back(&two);
    pointers.push_back(&three);
    pointers.push_back(&one);

    SortPointers(pointers);

    ASSERT_EQUAL(pointers.size(), 3u);
    ASSERT_EQUAL(*pointers[0], 1);
    ASSERT_EQUAL(*pointers[1], 2);
    ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
    const size_t count = 7;

    int *source = new int[count];
    int *dest = new int[count];

    for (size_t i = 0; i < count; ++i) {
        source[i] = i + 1;
    }
    ReversedCopy(source, count, dest);
    const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
    ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

    // Области памяти могут перекрываться
    ReversedCopy(source, count - 1, source + 1);
    const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
    ASSERT_EQUAL(vector<int>(source, source + count), expected2);

    delete[] dest;
    delete[] source;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSwap);
    RUN_TEST(tr, TestSortPointers);
    RUN_TEST(tr, TestReverseCopy);
    return 0;
}
