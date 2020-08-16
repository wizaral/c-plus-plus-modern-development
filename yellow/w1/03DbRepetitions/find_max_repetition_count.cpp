#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::cin, std::cout, std::endl;

enum class Lang {
    DE,
    FR,
    IT,
};
struct Region {
    std::string std_name;
    std::string parent_std_name;
    std::map<Lang, std::string> names;
    int64_t population;
};

inline auto rank(const Region &r) {
    return std::tie(r.std_name, r.parent_std_name, r.names, r.population);
}
bool operator<(const Region &lhs, const Region &rhs) {
    return rank(lhs) < rank(rhs);
}

int FindMaxRepetitionCount(const std::vector<Region> &regions) {
    int result = 0;
    std::map<Region, int> count;
    for (const auto &r : regions)
        result = std::max(result, ++count[r]);
    return result;
}

int main() {
    cout << FindMaxRepetitionCount({
        {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
        {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},
        {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
        {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
        {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},
    });
    cout << endl;

    cout << FindMaxRepetitionCount({
        {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
        {"Russia", "Eurasia", {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}}, 89},
        {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}}, 89},
        {"Moscow", "Toulouse", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 89},
        {"Moscow", "Russia", {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}}, 31},
    });
    cout << endl;
}
