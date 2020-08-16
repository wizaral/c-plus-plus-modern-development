#pragma once
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "date.h"

class Database {
    std::map<Date, std::vector<std::string>> storage_;
    std::map<Date, std::set<std::string>> set_;
public:
    void Add(const Date &date, const std::string &event);
    void Print(std::ostream &os) const;

    int RemoveIf(std::function<bool(const Date &date, const std::string &event)> pred);
    std::vector<std::pair<Date, std::string>> FindIf(std::function<bool(const Date &date, const std::string &event)> pred) const;

    std::pair<Date, std::string> Last(const Date &date) const;
};

std::ostream &operator<<(std::ostream &os, const std::pair<Date, std::string> &p);
