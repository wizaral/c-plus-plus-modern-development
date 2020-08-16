#include <iostream>
#include <numeric>
using std::cin, std::cout, std::endl, std::gcd;

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

    friend bool operator==(const Rational & lhs, const Rational & rhs);
    friend Rational operator+(const Rational &lhs, const Rational &rhs);
    friend Rational operator-(const Rational &lhs, const Rational &rhs);
};

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {lhs.p * rhs.q + rhs.p * lhs.q, lhs.q * rhs.q};
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {lhs.p * rhs.q - rhs.p * lhs.q, lhs.q * rhs.q};
}

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.p == rhs.p && lhs.q == rhs.q;
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
