#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct Image {
    virtual ~Image() = default;
    virtual string show() = 0;
};

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

int main() {
    ImageProxy proxy("large.png");
    cout << proxy.show() << '\n';
}

