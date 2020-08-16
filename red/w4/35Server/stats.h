#pragma once

#include "http_request.h"

#include <map>
#include <string_view>
using namespace std;

class Stats {
    map<string_view, int> method_ = {
        {"GET", 0},
        {"PUT", 0},
        {"POST", 0},
        {"DELETE", 0},
        {"UNKNOWN", 0},
    };
    map<string_view, int> uri_ = {
        {"/", 0},
        {"/order", 0},
        {"/product", 0},
        {"/basket", 0},
        {"/help", 0},
        {"unknown", 0},
    };
public:
    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int> &GetMethodStats() const;
    const map<string_view, int> &GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);
