#include "profile.h"
#include "test_runner.h"

#include <future>
#include <iterator>
#include <map>
#include <set>
#include <string>
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

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats &other);
};

void ExploreLine(const set<string> &key_words, Stats &st, string &line) {
    LOG_DURATION("split 1 line");
    istringstream iss(move(line));
    vector<string> v(istream_iterator<string>(iss), {});

    for (auto &i : v)
        if (key_words.count(i))
            ++st.word_frequences[move(i)];
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, Page<vector<string>::iterator> page) {
    Stats result;

    for (auto &i : page)
        ExploreLine(key_words, result, i);
    return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
    vector<string> v;

    for (string line; getline(input, line); )
        v.push_back(move(line));

    vector<future<Stats>> result;
    for (auto i : Paginate(v, 100))
        result.push_back([key_words, &i] {
            return ExploreKeyWordsSingleThread(ref(key_words), i);
        });

    Stats st;
    for (auto &i : result)
        st += i.get();

    return st;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
        {"yangle", 6},
        {"rocks", 2},
        {"sucks", 1}};
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
