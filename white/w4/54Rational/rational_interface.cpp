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
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            cout << r.Numerator() << '/' << r.Denominator() << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}
