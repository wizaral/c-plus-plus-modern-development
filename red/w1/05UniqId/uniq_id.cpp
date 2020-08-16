#include <string>
#include <vector>
using std::string, std::vector;

#define ID(x) VAR_##x
#define TOKEN(x) ID(x)
#define UNIQ_ID TOKEN(__LINE__)

int main() {
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}
