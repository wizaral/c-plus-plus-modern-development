#include "phone_number.h"
#include <stdexcept>
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    if (international_number[0] != '+')
        throw std::invalid_argument("no + at begin of the code");

    size_t pos1 = international_number.find('-');
    size_t pos2 = international_number.find('-', pos1 + 1);
    if (pos1 == string::npos || pos2 == string::npos)
        throw std::invalid_argument("no delimiters `-`");
    if (pos2 == pos1 + 1)
        throw std::invalid_argument("no city number");

    istringstream iss(international_number);
    iss.ignore();

    getline(iss, country_code_, '-');
    getline(iss, city_code_, '-');
    getline(iss, local_number_);
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return ((((string("+") += country_code_) += '-') += city_code_) += '-') += local_number_;
}
