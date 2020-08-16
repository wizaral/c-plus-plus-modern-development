#pragma once
#include <iomanip>
#include <iostream>
#include <tuple>

class Date {
    int year_ = 0, month_ = 0, day_ = 0;
public:
    Date() = default;
    Date(int year, int month, int day);

    int year() const;
    int month() const;
    int day() const;

    friend bool operator<(const Date &lhs, const Date &rhs);
    friend bool operator>(const Date &lhs, const Date &rhs);

    friend bool operator<=(const Date &lhs, const Date &rhs);
    friend bool operator>=(const Date &lhs, const Date &rhs);

    friend bool operator==(const Date &lhs, const Date &rhs);
    friend bool operator!=(const Date &lhs, const Date &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
private:
    constexpr std::tuple<const int &, const int &, const int &> rank() const;
};

Date ParseDate(std::istream &is);
