#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct TreeType {
    string name;
    string color;
};

class TreeFactory {
    map<string, shared_ptr<TreeType>> cache_;

public:
    shared_ptr<TreeType> get(const string& name, const string& color) {
        string key = name + ":" + color;
        if (!cache_[key]) cache_[key] = make_shared<TreeType>(TreeType{name, color});
        return cache_[key];
    }

    size_t count() const { return cache_.size(); }
};

struct Tree {
    int x;
    int y;
    shared_ptr<TreeType> type;
};

int main() {
    TreeFactory factory;
    vector<Tree> trees{{1, 2, factory.get("maple", "red")}, {3, 4, factory.get("maple", "red")}};
    cout << trees.size() << " trees share " << factory.count() << " type\n";
}

