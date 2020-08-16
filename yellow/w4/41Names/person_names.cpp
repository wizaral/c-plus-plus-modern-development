#include <iostream>
#include <map>
#include <string>
using namespace std;

class Person {
    map<int, string> fnames;
    map<int, string> lnames;
public:
    void ChangeFirstName(int year, const string &first_name) {
        fnames[year] = first_name;
    }
    void ChangeLastName(int year, const string &last_name) {
        lnames[year] = last_name;
    }
    string GetFullName(int year) {
        string fname, lname;
        GetInfo(fnames, fname, year);
        GetInfo(lnames, lname, year);

        if (fname.empty() == false && lname.empty() == false)
            return fname + " " + lname;
        else if (fname.empty() == false)
            return fname + " with unknown last name";
        else if (lname.empty() == false)
            return lname + " with unknown first name";
        return "Incognito";
    }
private:
    static void GetInfo(const map<int, string> &data, string &name, int year) {
        if (auto after = data.upper_bound(year); after != begin(data))
            name = prev(after)->second;
    }
};
