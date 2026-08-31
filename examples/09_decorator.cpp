#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Drink {
    virtual ~Drink() = default;
    virtual string name() const = 0;
    virtual int price() const = 0;
};

struct Tea : Drink {
    string name() const override { return "tea"; }
    int price() const override { return 30; }
};

class DrinkDecorator : public Drink {
protected:
    unique_ptr<Drink> inner_;

public:
    explicit DrinkDecorator(unique_ptr<Drink> inner) : inner_(move(inner)) {}
};

class Milk : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    string name() const override { return inner_->name() + "+milk"; }
    int price() const override { return inner_->price() + 10; }
};

class Boba : public DrinkDecorator {
public:
    using DrinkDecorator::DrinkDecorator;
    string name() const override { return inner_->name() + "+boba"; }
    int price() const override { return inner_->price() + 15; }
};

int main() {
    unique_ptr<Drink> drink = make_unique<Boba>(make_unique<Milk>(make_unique<Tea>()));
    cout << drink->name() << " $" << drink->price() << '\n';
}

