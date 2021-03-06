#include <algorithm>
#include <map>
#include <string>
#include <vector>

using std::string, std::vector;

class Person {
    std::map<int, std::pair<string, string>> names;
    int birth_year;
public:
    Person() = delete;
    Person(const string &fname, const string &lname, int year) 
        : names({{year, {fname, lname}}})
        , birth_year(year) {}

    void ChangeFirstName(int year, const string &fname) {
        if (year > birth_year)
            names[year].first = fname;
    }
    void ChangeLastName(int year, const string &lname) {
        if (year > birth_year)
            names[year].second = lname;
    }

    string GetFullName(int year) const {
        if (year < birth_year)
            return {"No person"};
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

    string GetFullNameWithHistory(int year) const {
        if (year < birth_year)
            return {"No person"};

        vector<string> fnames, lnames;
        collect_data(year, fnames, lnames);

        if (fnames.empty() == false && lnames.empty() == false) {
            string result = fnames.back();
            if (fnames.size() > 1)
                add_fnames(result, fnames);
            result += " ";
            result += lnames.back();
            if (lnames.size() > 1)
                add_lnames(result, lnames);
            return result;
        } else if (fnames.empty() == false) {
            string result = fnames.back();
            if (fnames.size() > 1)
                add_fnames(result, fnames);
            return result + " with unknown last name";
        } else if (lnames.empty() == false) {
            string result = lnames.back();
            if (lnames.size() > 1)
                add_lnames(result, lnames);
            return result + " with unknown first name";
        }
        return {"Incognito"};
    }
private:
    void collect_data(int year, vector<string> &fnames, vector<string> &lnames) const {
        for (const auto &[y, n] : names) {
            if (y > year)
                break;
            if (n.first.empty() == false)
                fnames.push_back(n.first);
            if (n.second.empty() == false)
                lnames.push_back(n.second);
        }
        fnames.erase(std::unique(begin(fnames), end(fnames)), end(fnames));
        lnames.erase(std::unique(begin(lnames), end(lnames)), end(lnames));
    }

    void add_fnames(string &fname, vector<string> &fnames) const {
        fname += " (";
        for (int i = fnames.size() - 2; i > 0; --i) {
            fname += fnames[i];
            fname += ", ";
        }
        fname += fnames.front();
        fname += ")";
    }

    void add_lnames(string &lname, vector<string> &lnames) const {
        lname += " (";
        for (int i = lnames.size() - 2; i > 0; --i) {
            lname += lnames[i];
            lname += ", ";
        }
        lname += lnames.front();
        lname += ")";
    }
};
