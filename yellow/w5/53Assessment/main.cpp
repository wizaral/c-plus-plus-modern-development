#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Person {
protected:
    const string name_;

    ostream &shortcut(ostream &os) const {
        return os << type() << ": " << name_;
    }

public:
    Person(const string &name)
        : name_(name) {}

    virtual void walk(const string &destination) const {
        shortcut(cout) << " walks to: " << destination << endl;
    }
    const string &name() const {
        return name_;
    }

    virtual const string &type() const = 0;
};

/* ========================================================================== */

class Student : public Person {
    inline static const string type_{"Student"};
    const string favourite_song;

public:
    Student(const string &name, const string &favourite_song)
        : Person(name), favourite_song(favourite_song) {}

    void learn() const {
        shortcut(cout) << " learns" << endl;
    }
    void sing_song() const {
        shortcut(cout) << " sings a song: " << favourite_song << endl;
    }

    void walk(const string &destination) const override {
        Person::walk(destination);
        sing_song();
    }
    const string &type() const override {
        return type_;
    }
};

/* ========================================================================== */

class Teacher : public Person {
    inline static const string type_{"Teacher"};
    const string subject;

public:
    Teacher(const string &name, const string &subject)
        : Person(name), subject(subject) {}

    void teach() {
        shortcut(cout) << " teaches: " << subject << endl;
    }

    const string &type() const override {
        return type_;
    }
};

/* ========================================================================== */

class Policeman : public Person {
    inline static const string type_{"Policeman"};

public:
    Policeman(const string &name)
        : Person(name) {}

    void check(const Person &p) {
        shortcut(cout) << " checks " << p.type() << ". " << p.type() << "'s name is: " << p.name() << endl;
    }

    const string &type() const override {
        return type_;
    }
};

void visit_places(const Person &person, const vector<string> &places) {
    for (const auto &p : places)
        person.walk(p);
}

int main() {
    Student s("Ann", "We will rock you");
    Teacher t("Jim", "Math");

    Policeman p1("Bob");
    Policeman p2("Dick");

    visit_places(s, {"Moscow", "London"});
    visit_places(t, {"Moscow", "London"});

    p1.check(s);
    p2.check(t);
}
