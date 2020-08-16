#include "stats.h"

void Stats::AddMethod(string_view method) {
    ++method_[method_.count(method) ? method : "UNKNOWN"];
}

void Stats::AddUri(string_view uri) {
    ++uri_[uri_.count(uri) ? uri : "unknown"];
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return method_;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return uri_;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest hr;
    size_t pos = 0;

    for (auto *it : {&hr.method, &hr.uri, &hr.protocol}) {
        line.remove_prefix(line.find_first_not_of(' '));
        pos = line.find(' ');
        *it = line.substr(0, pos);
        line.remove_prefix(pos + 1);
    }
    return hr;
}
