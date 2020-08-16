#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Figure {
public:
    virtual const string &Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle final : public Figure {
    inline static const string name = "TRIANGLE";
    int a, b, c;
public:
    Triangle(int a, int b, int c)
        : a(a), b(b), c(c) {}

    const string &Name() const override {
        return name;
    }
    double Perimeter() const override {
        return a + b + c;
    }
    double Area() const override {
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

class Rect final : public Figure {
    inline static const string name = "RECT";
    int a, b;
public:
    Rect(int a, int b)
        : a(a), b(b) {}

    const string &Name() const override {
        return name;
    }
    double Perimeter() const override {
        return 2 * a + 2 * b;
    }
    double Area() const override {
        return a * b;
    }
};

class Circle final : public Figure {
    inline static const string name = "CIRCLE";
    inline static const double pi = 3.14;
    int r;
public:
    Circle(int r)
        : r(r) {}

    const string &Name() const override {
        return name;
    }
    double Perimeter() const override {
        return 2 * pi * r;
    }
    double Area() const override {
        return pi * r * r;
    }
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
    string figure;

    if (is >> figure; figure == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if (figure == "RECT") {
        int a, b;
        is >> a >> b;
        return make_shared<Rect>(a, b);
    } else {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}