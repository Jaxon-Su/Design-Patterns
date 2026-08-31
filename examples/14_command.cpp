#include <iostream>
#include <string>

using namespace std;

class TextBuffer {
    string text_;

public:
    void append(const string& s) { text_ += s; }
    void erase_last(size_t n) { text_.erase(text_.size() - n); }
    string text() const { return text_; }
};

struct Command {
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AppendCommand : public Command {
    TextBuffer& buffer_;
    string value_;

public:
    AppendCommand(TextBuffer& buffer, string value) : buffer_(buffer), value_(move(value)) {}
    void execute() override { buffer_.append(value_); }
    void undo() override { buffer_.erase_last(value_.size()); }
};

int main() {
    TextBuffer buffer;
    AppendCommand cmd(buffer, "hello");
    cmd.execute();
    cmd.undo();
    cout << "'" << buffer.text() << "' after undo\n";
}

