#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

string AskTimeServer() {
#if 1
    // нормальный возврат строкового значения
    return "10:10:10";
#elif 0
    // выброс исключения system_error
    throw system_error();
#else
    // выброс другого исключения с сообщением.
    throw std::runtime_error("LOLKEK");
#endif
}

class TimeServer {
    string last_fetched_time = "00:00:00";
public:
    string GetCurrentTime() {
        try {
            last_fetched_time = AskTimeServer();
        } catch (const system_error &ex) {
        }
        return last_fetched_time;
    }
};

int main() {
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception &e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
