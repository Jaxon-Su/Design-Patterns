#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct SensorProfile {
    string model;
    int sample_rate;
    string station;

    unique_ptr<SensorProfile> clone() const {
        return make_unique<SensorProfile>(*this);
    }
};

int main() {
    SensorProfile base{"T100", 1000, "default"};
    auto copied = base.clone();
    copied->station = "Line-A";
    cout << copied->model << " at " << copied->station << '\n';
}

