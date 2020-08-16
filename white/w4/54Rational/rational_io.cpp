#include <iostream>
#include <sstream>
#include <numeric>

using std::cin, std::cout, std::endl;
using std::gcd, std::istream, std::ostream;
using std::istringstream, std::ostringstream;

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
    friend std::ostream &operator<<(std::ostream &os, const Rational &r);
    friend std::istream &operator>>(std::istream &is, Rational &r);
};

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.p == rhs.p && lhs.q == rhs.q;
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

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}
