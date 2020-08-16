#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
using namespace std;

auto FindNearestElement(const set<int> &numbers, int border) {
    if (auto after = numbers.lower_bound(border); after == begin(numbers)) {
        return after;
    } else if (auto behind = prev(after); after == end(numbers)) {
        return behind;
    } else
        return border - *behind <= *after - border ? behind : after;
}
