#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct Node {
    virtual ~Node() = default;
    virtual int size() const = 0;
};

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

int main() {
    Folder folder;
    folder.add(make_unique<File>(40));
    folder.add(make_unique<File>(60));
    cout << folder.size() << " KB\n";
}

