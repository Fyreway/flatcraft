#include <stdbool.h>

#include "event.h"
#include "render.h"
#include "state.h"

int main(void) {
    State state = init();

    bool running = true;

    while (running) {
        handle_events(&running, &state.game_state);
        render(&state);
    }

    cleanup(&state);
}
