#include <stdexcept>
#include <string>
using std::string, std::runtime_error;

void EnsureEqual(const string &left, const string &right) {
    if (left != right) {
        throw runtime_error(left + " != " + right);
    }
}
