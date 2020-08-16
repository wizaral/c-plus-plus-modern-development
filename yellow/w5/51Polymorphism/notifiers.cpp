#include <iostream>
#include <string>
using namespace std;

class INotifier {
public:
    virtual void Notify(const string &message) const = 0;
};

class SmsNotifier : public INotifier {
    string number;
public:
    explicit SmsNotifier(const string &s) : number(s) {}

    void Notify(const string &message) const override {
        SendSms(number, message);
    }
};

class EmailNotifier : public INotifier {
    string email;
public:
    explicit EmailNotifier(const string &s) : email(s) {}

    void Notify(const string &message) const override {
        SendEmail(email, message);
    }
};
