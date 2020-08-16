#include "test_runner.h"
#include <future>
#include <vector>
using namespace std;

template <typename Iterator>
class Page {
    Iterator first_, last_;
    size_t size_;
public:
    Page(Iterator first, Iterator last, size_t size)
        : first_(first), last_(last), size_(size) {}

    auto begin() const {
        return first_;
    }
    auto end() const {
        return last_;
    }
    auto size() const {
        return size_;
    }
};

template <typename Iterator>
class Paginator {
    vector<Page<Iterator>> data_;
public:
    Paginator(Iterator b, Iterator e, size_t size) {
        size_t dist = distance(b, e);
        size_t blocks = dist / size;
        size_t pages = blocks + (dist % size != 0);

        for (size_t i = 0; i < blocks; ++i, b += size)
            data_.emplace_back(b, b + size, size);
        if (blocks != pages)
            data_.emplace_back(b, e, distance(b, e));
    }

    auto begin() const {
        return data_.begin();
    }
    auto end() const {
        return data_.end();
    }
    auto size() const {
        return data_.size();
    }
};

template <typename C>
auto Paginate(C &c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

template<class Container>
int64_t CalculateRangeSum(const Container &matrix) {
    int64_t sum = 0;

    for (const auto &i : matrix)
        for (auto j : i)
            sum += j;
    return sum;
}

int64_t CalculateMatrixSum(const vector<vector<int>> &matrix) {
    vector<future<int64_t>> futures;
    for (auto p : Paginate(matrix, 2000))
        futures.push_back(async([p] { return CalculateRangeSum(p); }));

    int64_t sum = 0;
    for (auto &f : futures)
        sum += f.get();
    return sum;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    RUN_TEST(TestRunner{}, TestCalculateMatrixSum);
}
