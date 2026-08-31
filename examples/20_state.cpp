#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Player;

struct PlayerState {
    virtual ~PlayerState() = default;
    virtual string play(Player& player) = 0;
};

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

struct PlayingState : PlayerState {
    string play(Player&) override { return "already playing"; }
};

struct StoppedState : PlayerState {
    string play(Player& player) override {
        player.state(make_shared<PlayingState>());
        return "start playing";
    }
};

int main() {
    Player player(make_shared<StoppedState>());
    cout << player.play() << ", " << player.play() << '\n';
}

