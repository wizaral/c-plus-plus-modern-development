#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <unordered_map>
using namespace std;

// using T = string;

template <typename T>
class PriorityCollection {
    using It = set<pair<int, int>>::iterator;

    unordered_map<int, pair<T, It>> data;   // <id, item>
    set<pair<int, int>> ids;                // <priority, id>
    int count_id = 0;
public:
    using Id = int;

    Id Add(T object) {
        auto it = ids.insert({0, ++count_id}).first;
        data[count_id] = {move(object), it};
        return count_id;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        for (ObjInputIt it = range_begin; it != range_end; ++it, ++ids_begin)
            *ids_begin = Add(move(*it));
    }

    bool IsValid(Id id) const {
        return data.count(id);
    }

    const T &Get(Id id) const {
        return data.at(id).first;
    }

    void Promote(Id id) {
        It it = data[id].second;
        auto value = ids.extract(it).value();

        ++value.first;
        data[id].second = ids.insert(value).first;
    }

    pair<const T&, int> GetMax() const {
        auto it = ids.rbegin();
        return {data.at(it->second).first, it->first};
    }

    pair<T, int> PopMax() {
        auto it = prev(ids.end());
        auto &obj = data[it->second];

        auto prior = it->first;
        T t = move(obj.first);

        data.erase(it->second);
        ids.erase(it);
        return {move(t), prior};
    }
};

class StringNonCopyable : public string {
public:
    using string::string; // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;
    StringNonCopyable(StringNonCopyable &&) = default;
    StringNonCopyable &operator=(const StringNonCopyable &) = delete;
    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    strings.Promote(red_id);
    strings.Promote(red_id);
    strings.Promote(yellow_id);

    cout << strings.Get(white_id) << endl;
    cout << strings.Get(yellow_id) << endl;
    cout << strings.Get(red_id) << endl;
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
