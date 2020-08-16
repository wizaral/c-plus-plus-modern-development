#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>
using std::cin, std::cout, std::endl, std::gcd;
using std::set, std::map, std::vector;

class Rational {
    int p, q;
public:
    Rational() : p(0), q(1) {}
    Rational(int p, int q) {
        update(p, q);
        this->p = p, this->q = q;
    }

    int Numerator() const {
        return p;
    }
    int Denominator() const {
        return q;
    }
private:
    static void update(int &p, int &q) {
        if (p && q) {
            int sign = ((p > 0 && q > 0) || (p < 0 && q < 0));
            for (int g = gcd(p, q); g != 1; g = gcd(p, q))
                p /= g, q /= g;

            p = sign ? abs(p) : -abs(p);
            q = abs(q);
        } else {
            p = 0;
            q = 1;
        }
    }

    friend bool operator==(const Rational &lhs, const Rational &rhs);
    friend bool operator<(const Rational &lhs, const Rational &rhs);
};

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.p == rhs.p && lhs.q == rhs.q;
}

bool operator<(const Rational &lhs, const Rational &rhs) {
    return ((double)lhs.p / lhs.q) < ((double)rhs.p / rhs.q);
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
