#include <iostream>
#include <string>

using namespace std;

class AppConfig {
    string env_ = "dev";

    AppConfig() = default;

public:
    static AppConfig& instance() {
        static AppConfig one;
        return one;
    }

    void env(string value) { env_ = value; }
    string env() const { return env_; }
};

int main() {
    AppConfig::instance().env("learning");
    cout << AppConfig::instance().env() << '\n';
}

