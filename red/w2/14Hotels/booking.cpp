#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Booking {
    struct Request {
        Request(int64_t time, const string &hotel_name, int client_id, int room_count)
            : time_(time)
            , hotel_name_(hotel_name)
            , client_id_(client_id)
            , room_count_(room_count) {}

        int64_t time_;
        string hotel_name_;
        int client_id_;
        int room_count_;

        static const int seconds_per_day = 86400;
    };

    deque<Request> requests_;
    unordered_map<string, uint64_t> rooms_;
    unordered_map<string, unordered_map<uint64_t, uint64_t>> clients_;

    void shrink_requests(int64_t time) {
        auto pivot = lower_bound(requests_.begin(), requests_.end(), Request{0, "", 0, 0},
            [time](const Request &lhs, const Request &rhs) {
                return lhs.time_ + rhs.seconds_per_day <= time;
            }
        );

        for (auto it = requests_.begin(); it != pivot; ++it) {
            clients_[it->hotel_name_][it->client_id_] -= it->room_count_;
            if (clients_[it->hotel_name_][it->client_id_] == 0)
                clients_[it->hotel_name_].erase(it->client_id_);

            rooms_[it->hotel_name_] -= it->room_count_;
        }
        requests_.erase(requests_.begin(), pivot);
    }

public:
    Booking() = default;

    void book(int64_t time, const string &hotel_name, int client_id, int room_count) {
        requests_.emplace_back(time, hotel_name, client_id, room_count);
        rooms_[hotel_name] += room_count;
        clients_[hotel_name][client_id] += room_count;

        shrink_requests(time);
    }

    size_t clients(const string &hotel_name) {
        return clients_[hotel_name].size();
    }
    size_t rooms(const string &hotel_name) {
        return rooms_[hotel_name];
    }

    size_t clients(const string &hotel_name) const {
        if (clients_.count(hotel_name))
            return clients_.at(hotel_name).size();
        return 0;
    }
    size_t rooms(const string &hotel_name) const {
        if (rooms_.count(hotel_name))
            return rooms_.at(hotel_name);
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Booking booking;
    int query_count;
    cin >> query_count;

    string query_type;
    int64_t time;
    string hotel_name;
    int client_id;
    int room_count;

    for (int i = 0; i < query_count; ++i) {
        cin >> query_type;

        if (query_type == "BOOK") {
            cin >> time >> hotel_name >> client_id >> room_count;
            booking.book(time, hotel_name, client_id, room_count);
        } else if (cin >> hotel_name; query_type == "CLIENTS") {
            cout << booking.clients(hotel_name) << '\n';
        } else if (query_type == "ROOMS") {
            cout << booking.rooms(hotel_name) << '\n';
        }
    }
}
