#include "event.h"

#include <SDL.h>
#include "SDL_keyboard.h"

void handle_events(bool *running, GameState *game_state) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: *running = false; break;
        default: break;
        }
    }

    const Uint8 *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[SDL_SCANCODE_W]) game_state->player.y += 0.8;
    if (key_states[SDL_SCANCODE_A]) game_state->player.x += 0.8;
    if (key_states[SDL_SCANCODE_S]) game_state->player.y -= 0.8;
    if (key_states[SDL_SCANCODE_D]) game_state->player.x -= 0.8;
}
