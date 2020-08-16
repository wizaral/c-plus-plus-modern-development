// #include <unordered_set>
// #include <vector>
// using namespace std;

// template <typename T>
// void RemoveDuplicates(vector<T> &elements) {
//     unordered_set<T> s;
//     for (const T &i : elements)
//         s.insert(i);
//     elements.assign(begin(s), end(s));
// }

#include <algorithm>
using namespace std;

template <class T>
void RemoveDuplicates(vector<T> &elements) {
    sort(begin(elements), end(elements));
    elements.erase(unique(begin(elements), end(elements)), end(elements));
}
