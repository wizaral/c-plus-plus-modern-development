#include "sum_reverse_sort.h"
#include <algorithm>

int Sum(int x, int y) {
    return x + y;
}

string Reverse(string s) {
    for (int i = 0, j = s.size() - 1; i < j; ++i, --j)
        swap(s[i], s[j]);
    return s;
}

void Sort(vector<int>& nums) {
    sort(nums.begin(), nums.end());
}
