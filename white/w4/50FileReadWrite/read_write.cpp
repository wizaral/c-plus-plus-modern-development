#include <fstream>
#include <string>
using std::fstream, std::ios, std::string, std::getline, std::endl;
int main() {
    if (fstream is("input.txt", ios::in), os("output.txt", ios::out); is && os)
        for (string str; getline(is, str); os << str << endl);
}
