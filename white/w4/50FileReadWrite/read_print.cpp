#include <fstream>
#include <iostream>
#include <string>
using std::ifstream, std::string, std::getline, std::cout, std::endl;
int main() {
    if (ifstream is("input.txt"); is)
        for (string str; getline(is, str); cout << str << endl);
}
