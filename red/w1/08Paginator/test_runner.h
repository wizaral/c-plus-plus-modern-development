#pragma once

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &s) {
    return os << "{" << s.first << ", " << s.second << "}";
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &s) {
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
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
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
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &[key, value] : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << key << ": " << value;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << "\nhint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
    int fail_count = 0;
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception &e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown std::exception caught" << std::endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }
};

#define ASSERT_EQUAL(x, y)                                \
    do {                                                  \
        std::ostringstream __assert_private_os;                \
        __assert_private_os << #x << " != " << #y << std::endl \
            << __FILE__ << ":" << __LINE__;               \
        AssertEqual(x, y, __assert_private_os.str());     \
    } while (0)

#define ASSERT(x)                                  \
    do {                                           \
        std::ostringstream __assert_private_os;         \
        __assert_private_os << #x << " is false, " \
            << __FILE__ << ":" << __LINE__;        \
        Assert(x, __assert_private_os.str());      \
    } while (0)

#define RUN_TEST(tr, func) \
    tr.RunTest(func, #func)
