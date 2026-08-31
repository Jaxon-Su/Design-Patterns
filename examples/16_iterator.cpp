#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Playlist {
    vector<string> songs_{"Intro", "Loop", "Finale"};

public:
    vector<string>::const_iterator begin() const { return songs_.begin(); }
    vector<string>::const_iterator end() const { return songs_.end(); }
};

int main() {
    Playlist playlist;
    for (const auto& song : playlist) cout << song << ' ';
    cout << '\n';
}

