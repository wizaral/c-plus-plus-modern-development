#include <algorithm>
#include <string>
using std::string;

class ReversibleString {
    string str;
public:
    ReversibleString() = default;
    ReversibleString(const string &str) : str(str) {}

    void Reverse() {
        std::reverse(begin(str), end(str));
    }
    string ToString() const {
        return str;
    }
};
