#include <iostream>
#include <string>

using namespace std;

class DrinkRecipe {
public:
    virtual ~DrinkRecipe() = default;
    string make() const { return "boil -> " + brew() + " -> cup"; }

private:
    virtual string brew() const = 0;
};

class Coffee : public DrinkRecipe {
    string brew() const override { return "drip coffee"; }
};

int main() {
    cout << Coffee().make() << '\n';
}

