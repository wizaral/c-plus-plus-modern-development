#include <fstream>
#include <iostream>
#include <iomanip>

static inline void read_write(std::ifstream &is, char delim = '\0') {
    int temp;
    is >> temp;
    is.ignore();

    std::cout << std::setw(10) << temp;
    if (delim != '\0') {
        std::cout << delim;
    }
}

int main() {
    if (std::ifstream is("input.txt"); is) {
        int rows, columns;
        is >> rows >> columns;

        for (int i = rows - 1; i > 0; --i, read_write(is, '\n'))
            for (int j = columns - 1; j > 0; --j)
                read_write(is, ' ');
        for (int j = columns - 1; j > 0; --j)
            read_write(is, ' ');
        read_write(is);
    }
}
