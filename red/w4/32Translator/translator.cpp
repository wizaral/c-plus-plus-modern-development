#include "test_runner.h"
#include <deque>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

class Translator {
    using Container = unordered_map<string_view, string_view>;
    deque<string> data;
    Container forward;
    Container reverse;
public:
    Translator() = default;
    void Add(string_view source, string_view target) {
        string_view src = save(source);
        string_view trg = save(target);

        forward[src] = trg;
        reverse[trg] = src;
    }
    string_view TranslateForward(string_view source) const {
        return translate(forward, source);
    }
    string_view TranslateBackward(string_view target) const {
        return translate(reverse, target);
    }
private:
    string_view translate(const Container &cont, string_view sv) const {
        if (auto it = cont.find(sv); it != cont.end())
            return it->second;
        return {};
    }

    string_view save(string_view sv) {
        for (const auto *ptr : {&forward, &reverse})
            if (const auto it = ptr->find(sv); it != ptr->end())
                return it->first;
        return data.emplace_back(move(string(sv)));
    }
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    RUN_TEST(TestRunner{}, TestSimple);
}
