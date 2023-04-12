#include "event.hpp"

#include <SDL.h>

void flat::handle_events(bool &running, State &state) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: running = false; break;
        default: break;
        }
    }

    const std::uint8_t *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[SDL_SCANCODE_A]) state.player.x -= 0.2;
    if (key_states[SDL_SCANCODE_D]) state.player.x += 0.2;
    if (key_states[SDL_SCANCODE_SPACE] && state.player.vert_vel == 0) {
        state.player.vert_vel = -1;
    }
}
