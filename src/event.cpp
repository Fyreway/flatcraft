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
    if (key_states[SDL_SCANCODE_W]) state.player.y--;
    if (key_states[SDL_SCANCODE_A]) state.player.x--;
    if (key_states[SDL_SCANCODE_S]) state.player.y++;
    if (key_states[SDL_SCANCODE_D]) state.player.x++;
}
