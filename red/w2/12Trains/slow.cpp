#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

class RouteManager {
    map<int, set<int>> reachable_lists_;
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        if (reachable_lists_.count(start)) {
            const set<int> &stations = reachable_lists_.at(start);
            auto fin = stations.lower_bound(finish);
            if (fin != end(stations))
                result = min(result, abs(finish - *fin));
            if (fin != begin(stations))
                result = min(result, abs(finish - *prev(fin)));
        }
        return result;
    }
};

int main() {
    ostream::sync_with_stdio(false);
    cin.tie(nullptr);
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
}
