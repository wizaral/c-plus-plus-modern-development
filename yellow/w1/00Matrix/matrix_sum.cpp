#include <iostream>
#include <stdexcept>
#include <vector>

using std::cin, std::cout, std::endl;

class Matrix {
    int rows, columns;
    std::vector<std::vector<int>> matrix;

public:
    Matrix() : rows(0), columns(0) {}
    Matrix(int rows, int columns) {
        Reset(rows, columns);
    }
    void Reset(int r, int c) {
        if (r < 0 || c < 0)
            throw std::out_of_range("");
        if (r == 0 || c == 0)
            r = c = 0;
        matrix.assign(r, std::vector<int>(c));
        rows = r, columns = c;
    }

    int At(int r, int c) const {
        return matrix.at(r).at(c);
    }
    int &At(int r, int c) {
        return matrix.at(r).at(c);
    }

    int GetNumRows() const {
        return rows;
    }
    int GetNumColumns() const {
        return columns;
    }

    friend bool operator==(const Matrix &lhs, const Matrix &rhs);
    friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);
};

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    return lhs.rows == rhs.rows
        && lhs.columns == rhs.columns
        && lhs.matrix == rhs.matrix;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    if (lhs.rows != rhs.rows || lhs.columns != rhs.columns)
        throw std::invalid_argument("");

    Matrix result(lhs.rows, lhs.columns);
    for (int row = 0; row < result.rows; ++row)
        for (int column = 0; column < result.columns; ++column)
            result.At(row, column) = lhs.At(row, column) + rhs.At(row, column);
    return result;
}

std::istream &operator>>(std::istream &is, Matrix &m) {
    int rows, columns;
    is >> rows >> columns;

    m.Reset(rows, columns);
    for (int row = 0; row < rows; ++row)
        for (int column = 0; column < columns; ++column)
            is >> m.At(row, column);
    return is;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    os << m.rows << ' ' << m.columns << endl;
    for (int row = 0; row < m.rows; ++row) {
        os << m.At(row, 0);
        for (int column = 1; column < m.columns; ++column)
            os << ' ' << m.At(row, column);
        os << endl;
    }
    return os;
}

int main() {
    Matrix one, two;
    cin >> one >> two;
    cout << one + two << endl;
    cout << (one == two) << endl;
}
