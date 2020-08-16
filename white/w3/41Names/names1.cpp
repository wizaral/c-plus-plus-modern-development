#include <algorithm>
#include <iostream>
#include <string>
#include <map>
using std::string, std::map, std::pair;

class Person {
    map<int, pair<string, string>> names;
public:
    void ChangeFirstName(int year, const string &first_name) {
        names[year].first = first_name;
    }
    void ChangeLastName(int year, const string &last_name) {
        names[year].second = last_name;
    }
    string GetFullName(int year) {
        string fname, lname;

        for (const auto &[y, n] : names) {
            if (y > year)
                break;
            if (n.first.empty() == false)
                fname = n.first;
            if (n.second.empty() == false)
                lname = n.second;
        }

        if (fname.empty() == false && lname.empty() == false)
            return fname + " " + lname;
        else if (fname.empty() == false)
            return fname + " with unknown last name";
        else if (lname.empty() == false)
            return lname + " with unknown first name";
        return {"Incognito"};
    }
};
