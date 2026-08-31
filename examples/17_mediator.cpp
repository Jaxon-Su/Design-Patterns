#include <iostream>
#include <string>

using namespace std;

class Field {
    string value_;

public:
    void value(string v) { value_ = move(v); }
    string value() const { return value_; }
};

class LoginDialog {
    Field user_;
    Field password_;

public:
    Field& user() { return user_; }
    Field& password() { return password_; }
    bool can_login() const { return !user_.value().empty() && password_.value().size() >= 4; }
};

int main() {
    LoginDialog dialog;
    dialog.user().value("jaxon");
    dialog.password().value("1234");
    cout << boolalpha << dialog.can_login() << '\n';
}

