#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Button { virtual ~Button() = default; virtual string draw() const = 0; };
struct Checkbox { virtual ~Checkbox() = default; virtual string draw() const = 0; };
struct LightButton : Button { string draw() const override { return "light button"; } };
struct DarkButton : Button { string draw() const override { return "dark button"; } };
struct LightCheckbox : Checkbox { string draw() const override { return "light checkbox"; } };
struct DarkCheckbox : Checkbox { string draw() const override { return "dark checkbox"; } };

struct ThemeFactory {
    virtual ~ThemeFactory() = default;
    virtual unique_ptr<Button> button() const = 0;
    virtual unique_ptr<Checkbox> checkbox() const = 0;
};

struct DarkFactory : ThemeFactory {
    unique_ptr<Button> button() const override { return make_unique<DarkButton>(); }
    unique_ptr<Checkbox> checkbox() const override { return make_unique<DarkCheckbox>(); }
};

int main() {
    DarkFactory factory;
    cout << factory.button()->draw() << ", " << factory.checkbox()->draw() << '\n';
}

