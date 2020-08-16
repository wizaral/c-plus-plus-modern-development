#include "query.h"

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
