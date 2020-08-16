#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace TestRunnerPrivate {
template <class K, class V, template <class, class> class Map>
std::ostream &print_map(std::ostream &os, const Map<K, V> &m) {
    os << '[';
    if (auto it = m.begin(); it != m.end()) {
        os << '{' << it->first << ':' << it->second << '}';
        for (++it; it != m.end(); ++it)
            os << ", {" << it->first << ':' << it->second << '}';
    }
    return os << ']';
}

template <class Container>
std::ostream &print_container(std::ostream &os, const Container &arr) {
    os << '[';
    if (auto it = arr.begin(); it != arr.end()) {
        os << *it;
        for (++it; it != arr.end(); ++it)
            os << ", " << *it;
    }
    return os << ']';
}
} // namespace TestRunnerPrivate

template <class T, size_t S>
std::ostream &operator<<(std::ostream &os, const std::array<T, S> &arr) {
    return TestRunnerPrivate::print_container(os, arr);
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &d) {
    return TestRunnerPrivate::print_container(os, d);
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    return TestRunnerPrivate::print_container(os, v);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::forward_list<T> &fl) {
    return TestRunnerPrivate::print_container(os, fl);
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::list<T> &l) {
    return TestRunnerPrivate::print_container(os, l);
}

template <class K, class V>
std::ostream &operator<<(std::ostream &os, const std::map<K, V> &m) {
    return TestRunnerPrivate::print_map(os, m);
}
template <class K, class V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &m) {
    return TestRunnerPrivate::print_map(os, m);
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s) {
    return TestRunnerPrivate::print_container(os, s);
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T> &s) {
    return TestRunnerPrivate::print_container(os, s);
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const std::string &hint = "") {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty())
            os << "\nhint: " << hint;
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const std::string &hint = "") {
    AssertEqual(b, true, hint);
}

class TestRunner {
    int fail_count = 0;
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const std::string &test_name = "") {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception &ex) {
            ++fail_count;
            std::cerr << test_name << " fail: " << ex.what() << std::endl;
        } catch (...) {
            ++fail_count;
            std::cerr << "Unknown exception caught" << std::endl;
        }
    }

    ~TestRunner() {
        std::cerr.flush();
        if (fail_count > 0) {
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }
};

#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif

#define ASSERT_EQUAL(x, y)                     \
    do {                                       \
        std::ostringstream __assert_os;        \
        __assert_os                            \
            << #x << " != " << #y << std::endl \
            << FILE_NAME << ":" << __LINE__;   \
        AssertEqual(x, y, __assert_os.str());  \
    } while (0)

#define ASSERT(x)                             \
    do {                                      \
        std::ostringstream __assert_os;       \
        __assert_os                           \
            << #x << " is false" << std::endl \
            << FILE_NAME << ":" << __LINE__;  \
        Assert(x, __assert_os.str());         \
    } while (0)

#define RUN_TEST(tr, func) tr.RunTest(func, #func)
