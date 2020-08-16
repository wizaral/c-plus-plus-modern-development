#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::cin, std::cout, std::endl, std::setfill, std::setw;
using std::istringstream, std::istream_iterator;
using std::map, std::set, std::string, std::vector;
using std::tie, std::copy, std::inserter;
using isis = istream_iterator<string>;

class Data {
    struct Date {
        int year, month, day;
        Date(string &date) {
            istringstream iss(date);
            iss >> year;
            iss.ignore();
            iss >> month;
            iss.ignore();
            iss >> day;
        }
    };
    map<Date, set<string>> data;

public:
    bool add(vector<string> &v) {
        if (validate(v[1]))
            data[{v[1]}].insert(v[2]);
        else
            return false;
        return true;
    }
    bool del(vector<string> &v) {
        if (validate(v[1]))
            v.size() == 3 ? del({v[1]}, v[2]) : del({v[1]});
        else
            return false;
        return true;
    }
    bool find(vector<string> &v) const {
        if (validate(v[1]))
            find({v[1]});
        else
            return false;
        return true;
    }
    void print() const {
        for (const auto &[date, events] : data)
            for (const auto &event : events)
                cout << setw(4) << date.year << '-' << setw(2) << date.month << '-' << setw(2) << date.day << ' ' << event << endl;
    }
private:
    void del(const Date &date, const string &event) {
        if (data.count(date) && data[date].count(event)) {
            data[date].erase(event);
            cout << "Deleted successfully" << endl;
            if (data[date].empty())
                data.erase(date);
        } else
            cout << "Event not found" << endl;
    }
    void del(const Date &date) {
        cout << "Deleted " << data[date].size() << " events" << endl;
        data[date].clear();
        data.erase(date);
    }
    void find(const Date &date) const {
        if (data.count(date))
            for (const auto &i : data.at(date))
                cout << i << endl;
    }

    bool validate(const string &date) const {
        istringstream iss(date);
        int year, month, day;
        char delim1, delim2;

        if (iss >> year >> delim1 >> month >> delim2 >> day &&
            delim1 == '-' && delim2 == '-' && iss.eof()) {
            if (month > 0 && month < 13) {
                if (day > 0 && day < 32)
                    return true;
                else
                    cout << "Day value is invalid: " << day << endl;
            } else
                cout << "Month value is invalid: " << month << endl;
        } else
            cout << "Wrong date format: " << date << endl;
        return false;
    }
    friend bool operator<(const Date &lhs, const Date &rhs);
};

bool operator<(const Data::Date &lhs, const Data::Date &rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

int main() {
    Data db;
    vector<string> v;
    istringstream iss;
    cout << setfill('0');

    for (string command; getline(cin, command); iss.clear(), v.clear()) {
        iss.str(command);
        copy(isis(iss), {}, inserter(v, v.end()));

        if (v.empty() == false) {
            if (v.front() == "Add") {
                if (db.add(v) == false)
                    return 0;
            }
            else if (v.front() == "Del") {
                if (db.del(v) == false)
                    return 0;
            }
            else if (v.front() == "Find") {
                if (db.find(v) == false)
                    return 0;
            }
            else if (v.front() == "Print")
                db.print();
            else {
                cout << "Unknown command: " << v.front() << endl;
                return 0;
            }
        }
    }
}
