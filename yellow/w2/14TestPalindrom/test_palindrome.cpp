#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &name = {}) {
        try {
            func();
            cerr << name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrom(const string &str) {
    int i = 0, j = str.size() - 1;
    for (; i < j && str[i] == str[j]; ++i, --j);
    return i >= j;
}

void Test00() {
    string str{""};
    AssertEqual(IsPalindrom(str), true);
}
void Test01() {
    string str{"A"};
    AssertEqual(IsPalindrom(str), true);
}
void Test02() {
    string str{"AA"};
    AssertEqual(IsPalindrom(str), true);
}
void Test03() {
    string str{"ABA"};
    AssertEqual(IsPalindrom(str), true);
}
void Test04() {
    string str{" "};
    AssertEqual(IsPalindrom(str), true);
}
void Test05() {
    string str{"  "};
    AssertEqual(IsPalindrom(str), true);
}
void Test06() {
    string str{" . "};
    AssertEqual(IsPalindrom(str), true);
}
void Test07() {
    string str{"AbbA"};
    AssertEqual(IsPalindrom(str), true);
}
void Test08() {
    string str{"aBBa"};
    AssertEqual(IsPalindrom(str), true);
}
void Test09() {
    string str{"qwertyuiop   poiuytrewq"};
    AssertEqual(IsPalindrom(str), true);
}

void Test10() {
    string str{" .  "};
    AssertEqual(IsPalindrom(str), false);
}
void Test11() {
    string str{"Abba"};
    AssertEqual(IsPalindrom(str), false);
}
void Test12() {
    string str{"abbA"};
    AssertEqual(IsPalindrom(str), false);
}
void Test13() {
    string str{"ABBCA"};
    AssertEqual(IsPalindrom(str), false);
}
void Test14() {
    string str{" qwertyuiopqoiuytrewq"};
    AssertEqual(IsPalindrom(str), false);
}
void Test15() {
    string str{"                                           ."};
    AssertEqual(IsPalindrom(str), false);
}
void Test16() {
    string str{".                                           "};
    AssertEqual(IsPalindrom(str), false);
}
void Test17() {
    string str{"ffffffffffffffffffffffffffffffffffffaffffffffffffffffffffffffffffffff"};
    AssertEqual(IsPalindrom(str), false);
}
void Test18() {
    string str{"`1234567890-=qwertyuiop[]\\asdfghjkl;'zxcvbnm,./~!@#$%^&*()_+QWERTYUIOP{}|ASDFGHJKL:\"ZXCVBNM<>??F><MNBVCXZ\":LKJHGFDSA|}{POIUYTREWQ+_)(*&^%$#@!~/.,mnbvcxz';lkjhgfdsa\\][poiuytrewq=-0987654321`"};
    AssertEqual(IsPalindrom(str), false);
}
void Test19() {
    string str{"qwertyuiop  .poiuytrewq"};
    AssertEqual(IsPalindrom(str), false);
}

int main() {
    TestRunner runner;
    runner.RunTest(Test00, "Test00");
    runner.RunTest(Test01, "Test01");
    runner.RunTest(Test02, "Test02");
    runner.RunTest(Test03, "Test03");
    runner.RunTest(Test04, "Test04");
    runner.RunTest(Test05, "Test05");
    runner.RunTest(Test06, "Test06");
    runner.RunTest(Test07, "Test07");
    runner.RunTest(Test08, "Test08");
    runner.RunTest(Test09, "Test09");
    runner.RunTest(Test00, "Test00");

    runner.RunTest(Test11, "Test11");
    runner.RunTest(Test12, "Test12");
    runner.RunTest(Test13, "Test13");
    runner.RunTest(Test14, "Test14");
    runner.RunTest(Test15, "Test15");
    runner.RunTest(Test16, "Test16");
    runner.RunTest(Test17, "Test17");
    runner.RunTest(Test18, "Test18");
    runner.RunTest(Test19, "Test19");
    return 0;
}
