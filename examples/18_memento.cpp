#include <iostream>
#include <string>

using namespace std;

class Document {
    string text_;

public:
    explicit Document(string text) : text_(move(text)) {}
    string save() const { return text_; }
    void restore(const string& snapshot) { text_ = snapshot; }
    void edit(string text) { text_ = move(text); }
    string text() const { return text_; }
};

int main() {
    Document doc("v1");
    auto snapshot = doc.save();
    doc.edit("v2");
    doc.restore(snapshot);
    cout << doc.text() << '\n';
}

