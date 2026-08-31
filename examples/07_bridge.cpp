#include <iostream>
#include <string>

using namespace std;

struct Device {
    virtual ~Device() = default;
    virtual void on() = 0;
    virtual string status() const = 0;
};

class Projector : public Device {
    bool power_ = false;

public:
    void on() override { power_ = true; }
    string status() const override { return power_ ? "projector on" : "projector off"; }
};

class RemoteControl {
    Device& device_;

public:
    explicit RemoteControl(Device& device) : device_(device) {}
    void power_on() { device_.on(); }
};

int main() {
    Projector projector;
    RemoteControl remote(projector);
    remote.power_on();
    cout << projector.status() << '\n';
}

