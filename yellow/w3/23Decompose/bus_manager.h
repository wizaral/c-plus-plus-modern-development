#pragma once

#include <map>
#include <string>
#include <vector>

#include "responses.h"
using namespace std;

class BusManager {
    map<string, vector<string>> buses_;
    map<string, vector<string>> stops_;
public:
    void AddBus(const string &bus, const vector<string> &stops);
    BusesForStopResponse GetBusesForStop(const string &stop) const;
    StopsForBusResponse GetStopsForBus(const string &bus) const;
    AllBusesResponse GetAllBuses() const;
};
