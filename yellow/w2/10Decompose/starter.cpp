#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream &operator>>(istream &is, Query &q) {
    string temp;

    if (is >> temp; temp == "NEW_BUS") {
        int count;
        is >> q.bus >> count;
        q.type = QueryType::NewBus;

        q.stops.clear();
        q.stops.reserve(count);
        for (int i = 0; i < count; ++i) {
            is >> temp;
            q.stops.push_back(move(temp));
        }
    }
    else if (temp == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (temp == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (temp == "ALL_BUSES")
        q.type = QueryType::AllBuses;
    return is;
}

struct BusesForStopResponse {
    const vector<string> &buses;
    bool is_empty;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r) {
    if (!r.is_empty) {
        auto it = r.buses.begin(), end = r.buses.end();
        for (os << *it, ++it; it != end; os << *it, ++it)
            os << ' ';
    } else
        os << "No stop";
    return os;
}

struct StopsForBusResponse {
    const map<string, vector<string>> &buses;
    const vector<string> &stops;
    const string &bus;
    bool is_empty;
};

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

struct AllBusesResponse {
    const map<string, vector<string>> &buses;
};

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

class BusManager {
    map<string, vector<string>> buses_;
    map<string, vector<string>> stops_;
public:
    void AddBus(const string &bus, const vector<string> &stops) {
        for (const auto &stop : stops) {
            stops_[stop].push_back(bus);
            buses_[bus].push_back(stop);
        }
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const {
        return stops_.count(stop)
            ? BusesForStopResponse{stops_.at(stop), false}
            : BusesForStopResponse{{}, true};
    }
    StopsForBusResponse GetStopsForBus(const string &bus) const {
        return buses_.count(bus)
            ? StopsForBusResponse{stops_, buses_.at(bus), bus, false}
            : StopsForBusResponse{stops_, {}, bus, true};
    }
    AllBusesResponse GetAllBuses() const {
        return {buses_};
    }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;
    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}
