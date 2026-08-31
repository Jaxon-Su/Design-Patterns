#include <functional>
#include <iostream>

using namespace std;

using Discount = function<int(int)>;

class Cart {
    Discount discount_;

public:
    explicit Cart(Discount discount) : discount_(move(discount)) {}
    int checkout(int amount) const { return discount_(amount); }
};

int main() {
    Cart holiday([](int amount) { return amount * 80 / 100; });
    cout << holiday.checkout(1000) << '\n';
}

