#include <string>
#include <vector>

void MoveStrings(std::vector<std::string> &source, std::vector<std::string> &destination) {
    std::move(source.begin(), source.end(), std::back_inserter(destination));
    source.clear();
}
