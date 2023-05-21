#include <chrono>
#include <thread>

#include "event.hpp"
#include "render.hpp"
#include "state.hpp"

int main(void) {
    flat::State state;

    bool running = true;

    while (running) {
        flat::handle_events(running, state);
        flat::update(state);
        flat::render(state);

        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 64));
    }
}
