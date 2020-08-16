#include "bus_manager.h"

void BusManager::AddBus(const string &bus, const vector<string> &stops) {
    for (const auto &stop : stops) {
        stops_[stop].push_back(bus);
        buses_[bus].push_back(stop);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const {
    return stops_.count(stop)
        ? BusesForStopResponse{stops_.at(stop), false}
        : BusesForStopResponse{{}, true};
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const {
    return buses_.count(bus)
        ? StopsForBusResponse{stops_, buses_.at(bus), bus, false}
        : StopsForBusResponse{stops_, {}, bus, true};
}

AllBusesResponse BusManager::GetAllBuses() const {
    return {buses_};
}
