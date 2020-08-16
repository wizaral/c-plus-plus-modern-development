#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class ReadingManager {
    static const int MAX_PAGES_ = 1000;

    vector<unordered_set<int>> pages_to_id{MAX_PAGES_ + 1};
    unordered_map<int, int> id_to_pages;
public:
    ReadingManager() = default;

    void Read(int user_id, int page_count) {
        if (id_to_pages.count(user_id))
            pages_to_id[id_to_pages[user_id]].erase(user_id);
        id_to_pages[user_id] = page_count;
        pages_to_id[page_count].insert(user_id);
    }

    double Cheer(int user_id) const {
        if (id_to_pages.count(user_id) == 0)
            return 0;
        if (int user_count = id_to_pages.size(); user_count != 1) {
            int top_border = id_to_pages.at(user_id);
            int count = 0;

            for (int i = 1; i < top_border; ++i)
                count += pages_to_id[i].size();
            return count * 1.0L / (user_count - 1);
        }
        return 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;
    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
}
