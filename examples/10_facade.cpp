#include <iostream>
#include <string>

using namespace std;

class Loader { public: string load() const { return "raw-video"; } };
class Encoder { public: string encode(const string& data) const { return data + "->h264"; } };
class Writer { public: string write(const string& data) const { return "saved " + data; } };

class VideoExportFacade {
    Loader loader_;
    Encoder encoder_;
    Writer writer_;

public:
    string export_video() const {
        return writer_.write(encoder_.encode(loader_.load()));
    }
};

int main() {
    cout << VideoExportFacade().export_video() << '\n';
}

