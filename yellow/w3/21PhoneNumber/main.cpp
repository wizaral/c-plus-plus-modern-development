#include "phone_number.h"
#include "test_runner.h"

void Test0() {
    PhoneNumber number("+7-495-111-22-33");
    AssertEqual(number.GetCountryCode(), "7", "7");
    AssertEqual(number.GetCityCode(), "495", "495");
    AssertEqual(number.GetLocalNumber(), "111-22-33", "111-22-33");
    AssertEqual(number.GetInternationalNumber(), "+7-495-111-22-33", "GetInternationalNumber");
}
void Test1() {
    PhoneNumber number("+323-22-460002");
    AssertEqual(number.GetCountryCode(), "323", "323");
    AssertEqual(number.GetCityCode(), "22", "22");
    AssertEqual(number.GetLocalNumber(), "460002", "460002");
    AssertEqual(number.GetInternationalNumber(), "+323-22-460002", "GetInternationalNumber");
}
void Test2() {

    PhoneNumber number("+1-2-coursera-cpp");
    AssertEqual(number.GetCountryCode(), "1", "1");
    AssertEqual(number.GetCityCode(), "2", "2");
    AssertEqual(number.GetLocalNumber(), "coursera-cpp", "coursera-cpp");
    AssertEqual(number.GetInternationalNumber(), "+1-2-coursera-cpp", "GetInternationalNumber");
}

int main() {
    TestRunner r;
    r.RunTest(Test0, "Test0");
    r.RunTest(Test1, "Test1");
    r.RunTest(Test2, "Test2");
}
