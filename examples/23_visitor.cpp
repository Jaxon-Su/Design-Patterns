#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct Circle;
struct Rectangle;

struct Visitor {
    virtual ~Visitor() = default;
    virtual void visit(const Circle&) = 0;
    virtual void visit(const Rectangle&) = 0;
};

struct Shape {
    virtual ~Shape() = default;
    virtual void accept(Visitor& visitor) const = 0;
};

struct Circle : Shape {
    int radius;
    explicit Circle(int r) : radius(r) {}
    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

struct Rectangle : Shape {
    int width;
    int height;
    Rectangle(int w, int h) : width(w), height(h) {}
    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

class AreaVisitor : public Visitor {
    int total_ = 0;

public:
    void visit(const Circle& c) override { total_ += 3 * c.radius * c.radius; }
    void visit(const Rectangle& r) override { total_ += r.width * r.height; }
    int total() const { return total_; }
};

int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(2));
    shapes.push_back(make_unique<Rectangle>(3, 4));

    AreaVisitor visitor;
    for (const auto& shape : shapes) shape->accept(visitor);
    cout << visitor.total() << '\n';
}

