#include "event.hpp"
#include "render.hpp"
#include "state.hpp"

int main(void) {
    flat::State state;

    bool running = true;

    while (running) {
        handle_events(running, state);
        render(state);
    }
}
