#include "header.h"

int main() {
    std::vector<std::unique_ptr<Event>> event_pool;
    std::vector<std::unique_ptr<Trigger>> triggers;

    Unit hero, enemy;
    Trigger trigger;

    bool game_is_over = false; // To prevent you from starting
    while (!game_is_over) {
        // Check player mouse, keyboard
        event_pool.emplace_back(new MoveEvent(/*&hero, &enemy*/));
        trigger.AddEvent(*event_pool.back());
        game_is_over = true;
    }

    return 0;
}