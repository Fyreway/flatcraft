#include "state.hpp"

#include <SDL.h>

void flat::State::handle_events(bool &running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: running = false; break;
        case SDL_KEYDOWN:
            if (event.key.repeat)
                break;
            else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE
                     && player.stopped)
                player.vert_vel = 1;
            else if (event.key.keysym.scancode == SDL_SCANCODE_R
                     && player.targeted.has_value())
                change_block(player.targeted.value(), Block::Type::Bedrock);
            break;
        default: break;
        }
    }

    const std::uint8_t *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[SDL_SCANCODE_A]) player.move(chunks, -0.2);
    if (key_states[SDL_SCANCODE_D]) player.move(chunks, 0.2);
}
