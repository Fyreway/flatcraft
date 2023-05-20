#include "event.hpp"

#include <SDL.h>

void flat::handle_events(bool &running, State &state) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: running = false; break;
        case SDL_KEYDOWN:
            if (event.key.repeat) break;
            // if (event.key.keysym.scancode == SDL_SCANCODE_SPACE
            //     && state.player.stopped) {
            //     state.player.stopped = false;
            //     state.player.vert_vel = 2;
            // }
            if (event.key.keysym.scancode == SDL_SCANCODE_W)
                state.player.y += 5;
            break;
        default: break;
        }
    }

    const std::uint8_t *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[SDL_SCANCODE_A]) state.player.move(state.chunks, -0.2);
    if (key_states[SDL_SCANCODE_D]) state.player.move(state.chunks, 0.2);
}
