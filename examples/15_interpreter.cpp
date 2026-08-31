#include <iostream>
#include <map>
#include <memory>
#include <string>

using namespace std;

using Context = map<string, string>;

struct Expression {
    virtual ~Expression() = default;
    virtual bool interpret(const Context& context) const = 0;
};

class Equals : public Expression {
    string key_;
    string expected_;

public:
    Equals(string key, string expected) : key_(move(key)), expected_(move(expected)) {}

    bool interpret(const Context& context) const override {
        auto it = context.find(key_);
        return it != context.end() && it->second == expected_;
    }
};

class GreaterThan : public Expression {
    string key_;
    int limit_;

public:
    GreaterThan(string key, int limit) : key_(move(key)), limit_(limit) {}

    bool interpret(const Context& context) const override {
        auto it = context.find(key_);
        return it != context.end() && stoi(it->second) > limit_;
    }
};

class And : public Expression {
    unique_ptr<Expression> left_;
    unique_ptr<Expression> right_;

public:
    And(unique_ptr<Expression> left, unique_ptr<Expression> right)
        : left_(move(left)), right_(move(right)) {}

    bool interpret(const Context& context) const override {
        return left_->interpret(context) && right_->interpret(context);
    }
};

int main() {
    Context order{{"amount", "1200"}, {"customer", "vip"}};
    auto rule = make_unique<And>(
        make_unique<GreaterThan>("amount", 1000),
        make_unique<Equals>("customer", "vip"));
    cout << boolalpha << rule->interpret(order) << '\n';
}

