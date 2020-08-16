#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>
using namespace std;

vector<string> SplitIntoWords(const string &s) {
    istringstream iss(s);
    return vector<string>((istream_iterator<string>(iss)), {});
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
