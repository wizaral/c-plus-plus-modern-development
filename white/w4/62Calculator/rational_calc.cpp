#include <exception>
#include <iostream>
#include <numeric>
#include <string>

using std::cin, std::cout, std::endl, std::gcd;
using std::string, std::istream, std::ostream;

class Rational {
    int p, q;
public:
    Rational() : p(0), q(1) {}
    Rational(int p, int q) {
        if (q == 0)
            throw std::invalid_argument("Invalid argument");

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
        if (q == 0)
            throw std::invalid_argument("Invalid argument");
        int g = gcd(p, q);
        p /= g, q /= g;

        if (q < 0)
            p = -p, q = -q;
    }

    friend Rational &operator+=(Rational &lhs, const Rational &rhs);
    friend Rational &operator-=(Rational &lhs, const Rational &rhs);
    friend Rational &operator*=(Rational &lhs, const Rational &rhs);
    friend Rational &operator/=(Rational &lhs, const Rational &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Rational &r);
    friend std::istream &operator>>(std::istream &is, Rational &r);
};

Rational &operator+=(Rational &lhs, const Rational &rhs) {
    lhs.p = lhs.p * rhs.q + rhs.p * lhs.q;
    lhs.q *= rhs.q;
    return (Rational::update(lhs.p, lhs.q), lhs);
}
Rational &operator-=(Rational &lhs, const Rational &rhs) {
    lhs.p = lhs.p * rhs.q - rhs.p * lhs.q;
    lhs.q *= rhs.q;
    return (Rational::update(lhs.p, lhs.q), lhs);
}
Rational &operator*=(Rational &lhs, const Rational &rhs) {
    lhs.p *= rhs.p;
    lhs.q *= rhs.q;
    return (Rational::update(lhs.p, lhs.q), lhs);
}
Rational &operator/=(Rational &lhs, const Rational &rhs) {
    if (lhs.q * rhs.p == 0)
        throw std::domain_error("Division by zero");
    lhs.p *= rhs.q;
    lhs.q *= rhs.p;
    return (Rational::update(lhs.p, lhs.q), lhs);
}

std::ostream &operator<<(std::ostream &os, Rational const &r) {
    return os << r.p << '/' << r.q;
}
std::istream &operator>>(std::istream &is, Rational &r) {
    int p, q;
    char delim;

    if (is >> p >> delim >> q; !is.fail() && delim == '/')
        Rational::update(r.p = p, r.q = q);
    else
        throw std::runtime_error("Invalid argument");
    return is;
}

int main() {
    char operation;
    Rational r1, r2;

    try {
        cin >> r1 >> operation >> r2;
        switch (operation) {
            case '+':
                r1 += r2;
                break;
            case '-':
                r1 -= r2;
                break;
            case '*':
                r1 *= r2;
                break;
            case '/':
                r1 /= r2;
        }
        cout << r1 << endl;
    } catch (std::exception &ex) {
        cout << ex.what() << endl;
    }
}
