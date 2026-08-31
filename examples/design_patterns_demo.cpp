#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace abstract_factory {
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
struct LightFactory : ThemeFactory {
    unique_ptr<Button> button() const override { return make_unique<LightButton>(); }
    unique_ptr<Checkbox> checkbox() const override { return make_unique<LightCheckbox>(); }
};
struct DarkFactory : ThemeFactory {
    unique_ptr<Button> button() const override { return make_unique<DarkButton>(); }
    unique_ptr<Checkbox> checkbox() const override { return make_unique<DarkCheckbox>(); }
};
void run() {
    DarkFactory factory;
    cout << "Abstract Factory: " << factory.button()->draw() << ", " << factory.checkbox()->draw() << '\n';
}
}

namespace builder {
class Report {
public:
    vector<string> parts;
    string text() const {
        string out;
        for (const auto& part : parts) out += "[" + part + "]";
        return out;
    }
};
class ReportBuilder {
    Report report_;
public:
    ReportBuilder& title(string value) { report_.parts.push_back("title:" + value); return *this; }
    ReportBuilder& chart(string value) { report_.parts.push_back("chart:" + value); return *this; }
    ReportBuilder& table(string value) { report_.parts.push_back("table:" + value); return *this; }
    Report build() { return report_; }
};
void run() {
    auto report = ReportBuilder().title("Yield").chart("Trend").table("Summary").build();
    cout << "Builder: " << report.text() << '\n';
}
}

namespace factory_method {
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
class CityLogistics : public LogisticsApp {
    unique_ptr<Delivery> create_delivery() const override { return make_unique<TruckDelivery>(); }
};
class LabLogistics : public LogisticsApp {
    unique_ptr<Delivery> create_delivery() const override { return make_unique<DroneDelivery>(); }
};
void run() {
    LabLogistics app;
    cout << "Factory Method: " << app.plan() << '\n';
}
}

namespace prototype {
struct SensorProfile {
    string model;
    int sample_rate;
    string station;
    unique_ptr<SensorProfile> clone() const { return make_unique<SensorProfile>(*this); }
};
void run() {
    SensorProfile base{"T100", 1000, "default"};
    auto copied = base.clone();
    copied->station = "Line-A";
    cout << "Prototype: " << copied->model << " at " << copied->station << '\n';
}
}

namespace singleton {
class AppConfig {
    string env_ = "dev";
    AppConfig() = default;
public:
    static AppConfig& instance() { static AppConfig one; return one; }
    void env(string value) { env_ = move(value); }
    string env() const { return env_; }
};
void run() {
    AppConfig::instance().env("learning");
    cout << "Singleton: " << AppConfig::instance().env() << '\n';
}
}

namespace adapter {
class LegacyThermometer {
public:
    double fahrenheit() const { return 77.0; }
};
class CelsiusSensor {
    LegacyThermometer legacy_;
public:
    double celsius() const { return (legacy_.fahrenheit() - 32.0) * 5.0 / 9.0; }
};
void run() {
    cout << "Adapter: " << CelsiusSensor().celsius() << " C\n";
}
}

namespace bridge {
struct Device { virtual ~Device() = default; virtual void on() = 0; virtual string status() const = 0; };
class Projector : public Device {
    bool power_ = false;
public:
    void on() override { power_ = true; }
    string status() const override { return power_ ? "projector on" : "projector off"; }
};
class RemoteControl {
    Device& device_;
public:
    explicit RemoteControl(Device& device) : device_(device) {}
    void power_on() { device_.on(); }
};
void run() {
    Projector p;
    RemoteControl remote(p);
    remote.power_on();
    cout << "Bridge: " << p.status() << '\n';
}
}

namespace composite {
struct Node { virtual ~Node() = default; virtual int size() const = 0; };
struct File : Node {
    int bytes;
    explicit File(int value) : bytes(value) {}
    int size() const override { return bytes; }
};
struct Folder : Node {
    vector<unique_ptr<Node>> children;
    void add(unique_ptr<Node> node) { children.push_back(move(node)); }
    int size() const override {
        int total = 0;
        for (const auto& child : children) total += child->size();
        return total;
    }
};
void run() {
    Folder folder;
    folder.add(make_unique<File>(40));
    folder.add(make_unique<File>(60));
    cout << "Composite: " << folder.size() << " KB\n";
}
}

namespace decorator {
struct Drink { virtual ~Drink() = default; virtual string name() const = 0; virtual int price() const = 0; };
struct Tea : Drink { string name() const override { return "tea"; } int price() const override { return 30; } };
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
void run() {
    unique_ptr<Drink> drink = make_unique<Boba>(make_unique<Milk>(make_unique<Tea>()));
    cout << "Decorator: " << drink->name() << " $" << drink->price() << '\n';
}
}

namespace facade {
class Loader { public: string load() const { return "raw-video"; } };
class Encoder { public: string encode(const string& data) const { return data + "->h264"; } };
class Writer { public: string write(const string& data) const { return "saved " + data; } };
class VideoExportFacade {
    Loader loader_;
    Encoder encoder_;
    Writer writer_;
public:
    string export_video() const { return writer_.write(encoder_.encode(loader_.load())); }
};
void run() {
    cout << "Facade: " << VideoExportFacade().export_video() << '\n';
}
}

namespace flyweight {
struct TreeType { string name; string color; };
class TreeFactory {
    map<string, shared_ptr<TreeType>> cache_;
public:
    shared_ptr<TreeType> get(string name, string color) {
        string key = name + ":" + color;
        if (!cache_[key]) cache_[key] = make_shared<TreeType>(TreeType{move(name), move(color)});
        return cache_[key];
    }
    size_t count() const { return cache_.size(); }
};
struct Tree { int x; int y; shared_ptr<TreeType> type; };
void run() {
    TreeFactory factory;
    vector<Tree> trees{{1, 2, factory.get("maple", "red")}, {3, 4, factory.get("maple", "red")}};
    cout << "Flyweight: " << trees.size() << " trees share " << factory.count() << " type\n";
}
}

namespace proxy {
struct Image { virtual ~Image() = default; virtual string show() = 0; };
class BigImage : public Image {
    string path_;
public:
    explicit BigImage(string path) : path_(move(path)) {}
    string show() override { return "render " + path_; }
};
class ImageProxy : public Image {
    string path_;
    unique_ptr<BigImage> real_;
public:
    explicit ImageProxy(string path) : path_(move(path)) {}
    string show() override {
        if (!real_) real_ = make_unique<BigImage>(path_);
        return real_->show();
    }
};
void run() {
    ImageProxy proxy("large.png");
    cout << "Proxy: " << proxy.show() << '\n';
}
}

namespace chain_of_responsibility {
class Handler {
    unique_ptr<Handler> next_;
public:
    virtual ~Handler() = default;
    Handler& set_next(unique_ptr<Handler> next) { next_ = move(next); return *next_; }
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
void run() {
    auto chain = make_unique<FrontDesk>();
    chain->set_next(make_unique<Engineer>()).set_next(make_unique<Manager>());
    cout << "Chain: " << chain->handle(3) << '\n';
}
}

namespace command {
class TextBuffer {
    string text_;
public:
    void append(const string& s) { text_ += s; }
    void erase_last(size_t n) { text_.erase(text_.size() - n); }
    string text() const { return text_; }
};
struct Command { virtual ~Command() = default; virtual void execute() = 0; virtual void undo() = 0; };
class AppendCommand : public Command {
    TextBuffer& buffer_;
    string value_;
public:
    AppendCommand(TextBuffer& buffer, string value) : buffer_(buffer), value_(move(value)) {}
    void execute() override { buffer_.append(value_); }
    void undo() override { buffer_.erase_last(value_.size()); }
};
void run() {
    TextBuffer buffer;
    AppendCommand cmd(buffer, "hello");
    cmd.execute();
    cmd.undo();
    cout << "Command: '" << buffer.text() << "' after undo\n";
}
}

namespace iterator_pattern {
class Playlist {
    vector<string> songs_{"Intro", "Loop", "Finale"};
public:
    vector<string>::const_iterator begin() const { return songs_.begin(); }
    vector<string>::const_iterator end() const { return songs_.end(); }
};
void run() {
    Playlist playlist;
    cout << "Iterator:";
    for (const auto& song : playlist) cout << ' ' << song;
    cout << '\n';
}
}

namespace mediator {
class LoginDialog;
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
void run() {
    LoginDialog dialog;
    dialog.user().value("jaxon");
    dialog.password().value("1234");
    cout << "Mediator: login enabled=" << boolalpha << dialog.can_login() << '\n';
}
}

namespace memento {
class Document {
    string text_;
public:
    explicit Document(string text) : text_(move(text)) {}
    string save() const { return text_; }
    void restore(const string& snapshot) { text_ = snapshot; }
    void edit(string text) { text_ = move(text); }
    string text() const { return text_; }
};
void run() {
    Document doc("v1");
    auto snapshot = doc.save();
    doc.edit("v2");
    doc.restore(snapshot);
    cout << "Memento: " << doc.text() << '\n';
}
}

namespace observer {
struct Subscriber { virtual ~Subscriber() = default; virtual void update(int price) = 0; };
class PriceFeed {
    vector<Subscriber*> subscribers_;
public:
    void subscribe(Subscriber& sub) { subscribers_.push_back(&sub); }
    void publish(int price) { for (auto* sub : subscribers_) sub->update(price); }
};
class Dashboard : public Subscriber {
    int last_ = 0;
public:
    void update(int price) override { last_ = price; }
    int last() const { return last_; }
};
void run() {
    PriceFeed feed;
    Dashboard dashboard;
    feed.subscribe(dashboard);
    feed.publish(125);
    cout << "Observer: dashboard price=" << dashboard.last() << '\n';
}
}

namespace state {
class Player;
struct PlayerState { virtual ~PlayerState() = default; virtual string play(Player& player) = 0; };
class Player {
    shared_ptr<PlayerState> state_;
public:
    explicit Player(shared_ptr<PlayerState> state) : state_(move(state)) {}
    void state(shared_ptr<PlayerState> next) { state_ = move(next); }
    string play() {
        auto current = state_;
        return current->play(*this);
    }
};
struct PlayingState;
struct StoppedState : PlayerState { string play(Player& player) override; };
struct PlayingState : PlayerState { string play(Player&) override { return "already playing"; } };
string StoppedState::play(Player& player) {
    player.state(make_shared<PlayingState>());
    return "start playing";
}
void run() {
    Player player(make_shared<StoppedState>());
    cout << "State: " << player.play() << ", " << player.play() << '\n';
}
}

namespace strategy {
using Discount = function<int(int)>;
class Cart {
    Discount discount_;
public:
    explicit Cart(Discount discount) : discount_(move(discount)) {}
    int checkout(int amount) const { return discount_(amount); }
};
void run() {
    Cart holiday([](int amount) { return amount * 80 / 100; });
    cout << "Strategy: pay " << holiday.checkout(1000) << '\n';
}
}

namespace template_method {
class DrinkRecipe {
public:
    virtual ~DrinkRecipe() = default;
    string make() const { return "boil -> " + brew() + " -> cup"; }
private:
    virtual string brew() const = 0;
};
class Coffee : public DrinkRecipe { string brew() const override { return "drip coffee"; } };
void run() {
    cout << "Template Method: " << Coffee().make() << '\n';
}
}

namespace visitor {
struct Circle;
struct Rectangle;
struct Visitor { virtual ~Visitor() = default; virtual void visit(const Circle&) = 0; virtual void visit(const Rectangle&) = 0; };
struct Shape { virtual ~Shape() = default; virtual void accept(Visitor& visitor) const = 0; };
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
void run() {
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(2));
    shapes.push_back(make_unique<Rectangle>(3, 4));
    AreaVisitor visitor;
    for (const auto& shape : shapes) shape->accept(visitor);
    cout << "Visitor: area ~= " << visitor.total() << '\n';
}
}

int main() {
    abstract_factory::run();
    builder::run();
    factory_method::run();
    prototype::run();
    singleton::run();
    adapter::run();
    bridge::run();
    composite::run();
    decorator::run();
    facade::run();
    flyweight::run();
    proxy::run();
    chain_of_responsibility::run();
    command::run();
    iterator_pattern::run();
    mediator::run();
    memento::run();
    observer::run();
    state::run();
    strategy::run();
    template_method::run();
    visitor::run();
    return 0;
}
