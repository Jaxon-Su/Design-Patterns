#include <iostream>
#include <vector>

using namespace std;

struct Subscriber {
    virtual ~Subscriber() = default;
    virtual void update(int price) = 0;
};

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

int main() {
    PriceFeed feed;
    Dashboard dashboard;
    feed.subscribe(dashboard);
    feed.publish(125);
    cout << dashboard.last() << '\n';
}

