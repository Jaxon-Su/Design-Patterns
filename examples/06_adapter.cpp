#include <iostream>

using namespace std;

class LegacyThermometer {
public:
    double fahrenheit() const { return 77.0; }
};

class CelsiusSensor {
    LegacyThermometer legacy_;

public:
    double celsius() const {
        return (legacy_.fahrenheit() - 32.0) * 5.0 / 9.0;
    }
};

int main() {
    cout << CelsiusSensor().celsius() << " C\n";
}

