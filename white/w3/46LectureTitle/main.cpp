#include <iostream>
#include <string>

struct Specialization {
    std::string specialization;
    explicit Specialization(const std::string &s) : specialization(s) {}
};
struct Course {
    std::string course;
    explicit Course(const std::string &s) : course(s) {}
};
struct Week {
    std::string week;
    explicit Week(const std::string &s) : week(s) {}
};

struct LectureTitle {
    std::string specialization, course, week;
    LectureTitle(const Specialization &s, const Course &c, const Week &w)
        : specialization(s.specialization)
        , course(c.course)
        , week(w.week) {}
};
