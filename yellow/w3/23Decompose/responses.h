#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct BusesForStopResponse {
    const vector<string> &buses;
    bool is_empty;
};

struct StopsForBusResponse {
    const map<string, vector<string>> &buses;
    const vector<string> &stops;
    const string &bus;
    bool is_empty;
};

struct AllBusesResponse {
    const map<string, vector<string>> &buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);
ostream &operator<<(ostream &os, const StopsForBusResponse &r);
ostream &operator<<(ostream &os, const AllBusesResponse &r);
