#include "responses.h"

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (!r.is_empty) {
        auto it = r.buses.begin(), end = r.buses.end();
        for (os << *it, ++it; it != end; os << *it, ++it)
            os << ' ';
    } else
        os << "No stop";
    return os;
}

inline void print(ostream &os, const string &s, const map<string, vector<string>> &m, const string &b) {
    if (os << "Stop " << s << ':'; m.at(s).size() > 1) {
        for (const auto &b_ : m.at(s)) {
            if (b_ != b)
                os << ' ' << b_;
        }
    } else
        os << " no interchange";
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r) {
    if (!r.is_empty) {
        auto it = r.stops.begin(), end = r.stops.end();
        for (print(os, *it, r.buses, r.bus), ++it; it != end; print(os, *it, r.buses, r.bus), ++it)
            os << endl;
    } else
        os << "No bus";
    return os;
}

inline void print(ostream &os, const pair<string, vector<string>> &p) {
    os << "Bus " << p.first << ":";
    for (const auto &s : p.second)
        os << ' ' << s;
}

ostream &operator<<(ostream &os, const AllBusesResponse &r) {
    if (!r.buses.empty()) {
        auto it = r.buses.begin(), end = r.buses.end();
        for (print(os, *it), ++it; it != end; print(os, *it), ++it)
            os << endl;
    } else
        os << "No buses";
    return os;
}
