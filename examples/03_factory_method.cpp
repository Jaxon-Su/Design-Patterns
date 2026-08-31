#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Delivery { virtual ~Delivery() = default; virtual string deliver() const = 0; };
struct TruckDelivery : Delivery { string deliver() const override { return "truck delivers boxes"; } };
struct DroneDelivery : Delivery { string deliver() const override { return "drone delivers samples"; } };

class LogisticsApp {
public:
    virtual ~LogisticsApp() = default;
    string plan() const { return create_delivery()->deliver(); }

private:
    virtual unique_ptr<Delivery> create_delivery() const = 0;
};

class LabLogistics : public LogisticsApp {
    unique_ptr<Delivery> create_delivery() const override { return make_unique<DroneDelivery>(); }
};

int main() {
    LabLogistics app;
    cout << app.plan() << '\n';
}

