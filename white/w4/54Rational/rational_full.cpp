#include <exception>
#include <iostream>
#include <numeric>

using std::cin, std::cout, std::endl;
using std::gcd, std::istream, std::ostream;

class Rational {
    int p, q;
public:
    Rational() : p(0), q(1) {}
    Rational(int p, int q) {
        if (q == 0)
            throw std::invalid_argument("Denomenator is equal to zero!");

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

    friend bool operator<(const Rational &lhs, const Rational &rhs);
    friend bool operator>(const Rational &lhs, const Rational &rhs);
    friend bool operator<=(const Rational &lhs, const Rational &rhs);
    friend bool operator>=(const Rational &lhs, const Rational &rhs);
    friend bool operator==(const Rational &lhs, const Rational &rhs);
    friend bool operator!=(const Rational &lhs, const Rational &rhs);

    friend Rational &operator+(Rational &r);
    friend Rational &operator-(Rational &r);

    friend Rational operator+(const Rational &lhs, const Rational &rhs);
    friend Rational operator-(const Rational &lhs, const Rational &rhs);
    friend Rational operator*(const Rational &lhs, const Rational &rhs);
    friend Rational operator/(const Rational &lhs, const Rational &rhs);

    friend Rational &operator+=(Rational &lhs, const Rational &rhs);
    friend Rational &operator-=(Rational &lhs, const Rational &rhs);
    friend Rational &operator*=(Rational &lhs, const Rational &rhs);
    friend Rational &operator/=(Rational &lhs, const Rational &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Rational &r);
    friend std::istream &operator>>(std::istream &is, Rational &r);
};

bool operator<(const Rational &lhs, const Rational &rhs) {
    return ((double)lhs.p / lhs.q) < ((double)rhs.p / rhs.q);
}
bool operator>(const Rational &lhs, const Rational &rhs) {
    return ((double)lhs.p / lhs.q) > ((double)rhs.p / rhs.q);
}
bool operator<=(const Rational &lhs, const Rational &rhs) {
    return ((double)lhs.p / lhs.q) <= ((double)rhs.p / rhs.q);
}
bool operator>=(const Rational &lhs, const Rational &rhs) {
    return ((double)lhs.p / lhs.q) >= ((double)rhs.p / rhs.q);
}

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.p == rhs.p && lhs.q == rhs.q;
}
bool operator!=(const Rational &lhs, const Rational &rhs) {
    return lhs.p != rhs.p || lhs.q != rhs.q;
}

Rational &operator+(Rational &r) {
    return r;
}
Rational &operator-(Rational &r) {
    return (r.p *= -1, r);
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {lhs.p * rhs.q + rhs.p * lhs.q, lhs.q * rhs.q};
}
Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {lhs.p * rhs.q - rhs.p * lhs.q, lhs.q * rhs.q};
}
Rational operator*(const Rational &lhs, const Rational &rhs) {
    return {lhs.p * rhs.p, lhs.q * rhs.q};
}
Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (lhs.q * rhs.p == 0)
        throw std::domain_error("Division by zero!");
    return {lhs.p * rhs.q, lhs.q * rhs.p};
}

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
        throw std::domain_error("Division by zero!");
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
    return is;
}
