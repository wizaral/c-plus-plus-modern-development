#include "test_runner.h"

using namespace std;

template<typename T> class Table {
    vector<vector<T>> table;
    size_t m_rows, m_columns;
public:
    Table(size_t rows, size_t columns)
        : table(vector<vector<T>>(rows, vector<T>(columns))),
        m_rows(rows), m_columns(columns) {}

    pair<size_t, size_t> Size() {
        return pair(m_rows, m_columns);
    }

    const pair<size_t, size_t> Size() const {
        return pair(m_rows, m_columns);
    }

    const vector<T> &operator[](size_t row) const {
        return table[row];
    }
    vector<T> &operator[](size_t row) {
        return table[row];
    }

    void Resize(size_t rows, size_t columns) {
        if (rows != m_rows)
            table.resize(rows);
        if (columns != m_columns)
            for (auto &c : table)
                c.resize(columns);
        m_rows = rows;
        m_columns = columns;
    }
};

void TestTable() {
    Table<int> t(1, 1);
    ASSERT_EQUAL(t.Size().first, 1u);
    ASSERT_EQUAL(t.Size().second, 1u);
    t[0][0] = 42;
    ASSERT_EQUAL(t[0][0], 42);
    t.Resize(3, 4);
    ASSERT_EQUAL(t.Size().first, 3u);
    ASSERT_EQUAL(t.Size().second, 4u);
    t[0][0] = 21;
    t[0][1] = 42;
    t[1][0] = 42;
    ASSERT_EQUAL(t[0][0], 21);
    ASSERT_EQUAL(t[0][1], 42);
    ASSERT_EQUAL(t[1][0], 42);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestTable);
    return 0;
}
