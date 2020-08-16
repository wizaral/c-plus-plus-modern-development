#include <exception>
#include <iostream>
#include <numeric>
using namespace std;

class Rational {
    int p, q;
public:
    Rational() : p(0), q(1) {}
    Rational(int p, int q) {
        if (q == 0)
            throw invalid_argument("");

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
        int g = gcd(p, q);
        p /= g, q /= g;

        if (q < 0)
            p = -p, q = -q;
    }

    friend Rational operator/(const Rational &lhs, const Rational &rhs);
};

Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (lhs.q * rhs.p == 0)
        throw domain_error("");
    return {lhs.p * rhs.q, lhs.q * rhs.p};
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument &) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        x.Denominator();
        return 2;
    } catch (domain_error &) {
    }

    cout << "OK" << endl;
    return 0;
}
