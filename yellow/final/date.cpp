#include "date.h"
using namespace std;

Date::Date(int year, int month, int day)
    : year_(year), month_(month), day_(day) {}

int Date::year() const {
    return year_;
}
int Date::month() const {
    return month_;
}
int Date::day() const {
    return day_;
}

bool operator<(const Date &lhs, const Date &rhs) {
    return lhs.rank() < rhs.rank();
}
bool operator>(const Date &lhs, const Date &rhs) {
    return lhs.rank() > rhs.rank();
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return !(lhs > rhs);
}
bool operator>=(const Date &lhs, const Date &rhs) {
    return !(lhs < rhs);
}

bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.rank() == rhs.rank();
}
bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}

ostream &operator<<(ostream &os, const Date &date) {
    return os << setfill('0') << setw(4) << date.year_
        << '-' << setw(2) << date.month_
        << '-' << setw(2) << date.day_;
}

constexpr tuple<const int &, const int &, const int &> Date::rank() const {
    return tie(year_, month_, day_);
}

Date ParseDate(istream &is) {
    int year, month, day;

    is >> year;
    is.ignore();
    is >> month;
    is.ignore();
    is >> day;

    return {year, month, day};
}
