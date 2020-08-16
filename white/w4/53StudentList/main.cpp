#include <iostream>
#include <string>
#include <vector>

struct Student {
    Student(std::string &&fn, std::string &&ln, int &y, int &m, int &d)
        : fname(fn), lname(ln), year(y), month(m), day(d) {}
    std::string fname, lname;
    int year, month, day;
};

std::vector<Student> read_data(int size) {
    std::vector<Student> data;
    data.reserve(size);

    std::string fname, lname;
    int y, m, d;

    for (int i = 0; i < size; ++i) {
        std::cin >> fname >> lname >> d >> m >> y;
        data.emplace_back(move(fname), move(lname), y, m, d);
    }
    return data;
}

int main() {
    int size, count, number;
    std::string request;

    std::cin >> size;
    std::vector<Student> data = move(read_data(size));
    std::cin >> count;

    for (int i = 0; i < count; ++i) {
        std::cin >> request >> number;
        if (--number; number > -1 && number < size) {
            if (request == "name")
                std::cout << data[number].fname << ' ' << data[number].lname << std::endl;
            else if (request == "date")
                std::cout << data[number].day << '.' << data[number].month << '.' << data[number].year << std::endl;
            else
                std::cout << "bad request" << std::endl;
        } else
            std::cout << "bad request" << std::endl;
    }
}
