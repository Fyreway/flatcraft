#include <chrono>
#include <thread>

#include "state.hpp"

int main(void) {
    flat::State state;

    bool running = true;

    while (running) {
        state.handle_events(running);
        state.update();
        state.render();

        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 64));
    }
}
