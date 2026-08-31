#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Handler {
    unique_ptr<Handler> next_;

public:
    virtual ~Handler() = default;

    Handler& set_next(unique_ptr<Handler> next) {
        next_ = move(next);
        return *next_;
    }

    string handle(int severity) const {
        auto result = process(severity);
        if (!result.empty()) return result;
        return next_ ? next_->handle(severity) : "no handler";
    }

private:
    virtual string process(int severity) const = 0;
};

class FrontDesk : public Handler { string process(int s) const override { return s <= 1 ? "front desk" : ""; } };
class Engineer : public Handler { string process(int s) const override { return s <= 3 ? "engineer" : ""; } };
class Manager : public Handler { string process(int) const override { return "manager"; } };

int main() {
    auto chain = make_unique<FrontDesk>();
    chain->set_next(make_unique<Engineer>()).set_next(make_unique<Manager>());
    cout << chain->handle(3) << '\n';
}

