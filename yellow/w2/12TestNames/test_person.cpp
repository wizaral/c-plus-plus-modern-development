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
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
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

// class Person {
//     map<int, pair<string, string>> names;

// public:
//     void ChangeFirstName(int year, const string &first_name) {
//         names[year].first = first_name;
//     }
//     void ChangeLastName(int year, const string &last_name) {
//         names[year].second = last_name;
//     }
//     string GetFullName(int year) {
//         string fname, lname;

//         for (const auto &[y, n] : names) {
//             if (y > year)
//                 break;
//             if (n.first.empty() == false)
//                 fname = n.first;
//             if (n.second.empty() == false)
//                 lname = n.second;
//         }

//         if (fname.empty() == false && lname.empty() == false)
//             return fname + " " + lname;
//         else if (fname.empty() == false)
//             return fname + " with unknown last name";
//         else if (lname.empty() == false)
//             return lname + " with unknown first name";
//         return "Incognito";
//     }
// };

void TestOneYearOneName() {
    Person p;

    p.ChangeFirstName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex with unknown last name");
    p.ChangeFirstName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex with unknown last name");
    p.ChangeLastName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex Alex");
    p.ChangeLastName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex Alex");
    p.ChangeFirstName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex Alex");
}

void TestOneYear() {
    Person p;

    p.ChangeFirstName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex with unknown last name");
    p.ChangeFirstName(2000, "Dan");
    AssertEqual(p.GetFullName(2000), "Dan with unknown last name");

    p.ChangeLastName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Dan Alex");
    p.ChangeLastName(2000, "Dan");
    AssertEqual(p.GetFullName(2000), "Dan Dan");

    p.ChangeFirstName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex Dan");
    p.ChangeLastName(2000, "Alex");
    AssertEqual(p.GetFullName(2000), "Alex Alex");
}

void Test() {
    Person p;

    p.ChangeFirstName(1965, "Polina");
    p.ChangeLastName(1967, "Sergeeva");

    AssertEqual(p.GetFullName(1900), "Incognito");
    AssertEqual(p.GetFullName(1965), "Polina with unknown last name");
    AssertEqual(p.GetFullName(1990), "Polina Sergeeva");

    p.ChangeFirstName(1970, "Appolinaria");
    AssertEqual(p.GetFullName(1969), "Polina Sergeeva");
    AssertEqual(p.GetFullName(1970), "Appolinaria Sergeeva");

    p.ChangeLastName(1968, "Volkova");
    AssertEqual(p.GetFullName(1969), "Polina Volkova");
    AssertEqual(p.GetFullName(1970), "Appolinaria Volkova");
}

void TestMedium() {
    Person p;

    p.ChangeLastName(1965, "LOL");
    p.ChangeFirstName(1967, "KEK");

    AssertEqual(p.GetFullName(1964), "Incognito");
    AssertEqual(p.GetFullName(1966), "LOL with unknown first name");
    AssertEqual(p.GetFullName(1968), "KEK LOL");
}

void TestHard() {
    Person p;

    p.ChangeFirstName(1965, "Alex");
    p.ChangeLastName(1967, "Piers");

    AssertEqual(p.GetFullName(1964), "Incognito");
    AssertEqual(p.GetFullName(1966), "Alex with unknown last name");
    AssertEqual(p.GetFullName(1968), "Alex Piers");

    p.ChangeFirstName(1969, "Alexander");
    AssertEqual(p.GetFullName(1968), "Alex Piers");
    AssertEqual(p.GetFullName(1969), "Alexander Piers");
    AssertEqual(p.GetFullName(1970), "Alexander Piers");

    p.ChangeLastName(1968, "Wizaral");
    AssertEqual(p.GetFullName(1967), "Alex Piers");
    AssertEqual(p.GetFullName(1968), "Alex Wizaral");
    AssertEqual(p.GetFullName(1969), "Alexander Wizaral");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestOneYearOneName, "TestOneYearOneName");
    runner.RunTest(TestOneYear, "TestOneYear");
    runner.RunTest(Test, "Test");
    runner.RunTest(TestMedium, "TestMedium");
    runner.RunTest(TestHard, "TestHard");
}
