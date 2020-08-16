#include "database.h"
using namespace std;

void Database::Add(const Date &date, const string &event) {
    if (storage_.count(date) == 0 || set_.at(date).count(event) == 0) {
        storage_[date].push_back(event);
        set_[date].insert(event);
    }
}

void Database::Print(ostream &os) const {
    for (const auto &[date, events] : storage_) {
        for (const auto &event : events) {
            os << date << " " << event << endl;
        }
    }
}

int Database::RemoveIf(std::function<bool(const Date &date, const std::string &event)> pred) {
    int count = 0;

    for (auto its = storage_.begin(); its != storage_.end();) {
        auto itev = stable_partition(its->second.begin(), its->second.end(), [&](const string &str) {
            return !pred(its->first, str);
        });

        if (itev != its->second.end()) {
            count += distance(itev, its->second.end());
            its->second.erase(itev, its->second.end());
            set_[its->first].clear();
            set_[its->first].insert(its->second.begin(), its->second.end());
        };

        if (its->second.empty()) {
            set_.erase(its->first);
            its = storage_.erase(its);
        } else {
            ++its;
        }
    }
    return count;
}

vector<pair<Date, string>> Database::FindIf(std::function<bool(const Date &date, const std::string &event)> pred) const {
    vector<pair<Date, string>> result;

    for (auto its = storage_.begin(); its != storage_.end(); ++its) {
        for (auto itev = its->second.begin(); itev != its->second.end();) {
            itev = find_if(itev, its->second.end(), [&](const string &str) {
                return pred(its->first, str);
            });

            if (itev != its->second.end()) {
                result.emplace_back(its->first, *itev);
                ++itev;
            };
        }
        
    }
    return result;
}

pair<Date, string> Database::Last(const Date &date) const {
    if (storage_.empty() || date < storage_.begin()->first) {
        throw invalid_argument("");
    };

    auto it = --(storage_.upper_bound(date));
    return {it->first, it->second.back()};
}

ostream &operator<<(ostream &os, const pair<Date, string> &p) {
    return os << p.first << ' ' << p.second;
}
