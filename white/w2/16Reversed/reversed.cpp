#include <vector>

std::vector<int> Reversed(const std::vector<int> &v) {
    std::vector<int> r(v.size());
    std::copy_backward(v.rbegin(), v.rend(), r.end());
    return r;
}
