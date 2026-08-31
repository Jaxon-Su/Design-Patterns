#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

int main() {
    auto report = ReportBuilder().title("Yield").chart("Trend").table("Summary").build();
    cout << report.text() << '\n';
}

