#include <iostream>
#include <map>
using std::cin, std::cout, std::endl;

template<class T, class U>
U &GetRefStrict(std::map<T, U> &m, T key) {
    if (m.count(key) == 0)
        throw std::runtime_error("");
    return m[key];
}
