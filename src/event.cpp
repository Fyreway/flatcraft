#include "state.hpp"

void flat::State::handle_events(bool &running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT: running = false; break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_SPACE:
                if (player.stopped) player.vert_vel = 1;
                break;
            case SDL_SCANCODE_R:
                if (player.targeted.has_value()) {
                    if (player.focused_mat.has_value())
                        change_block(
                            player.targeted.value(),
                            player.inventory.at(player.focused_mat.value())
                                .first);
                }
                break;
            case SDL_SCANCODE_Y:
                if (player.targeted.has_value())
                    change_block(player.targeted.value(), std::nullopt);
                break;
            case SDL_SCANCODE_1: player.focused_mat = 0; break;
            case SDL_SCANCODE_2: player.focused_mat = 1; break;
            case SDL_SCANCODE_3: player.focused_mat = 2; break;
            case SDL_SCANCODE_4: player.focused_mat = 3; break;
            case SDL_SCANCODE_5: player.focused_mat = 4; break;
            case SDL_SCANCODE_6: player.focused_mat = 5; break;
            case SDL_SCANCODE_7: player.focused_mat = 6; break;
            case SDL_SCANCODE_8: player.focused_mat = 7; break;
            case SDL_SCANCODE_9: player.focused_mat = 8; break;
            default: break;
            }
            break;
        default: break;
        }
    }

    const std::uint8_t *key_states = SDL_GetKeyboardState(NULL);
    if (key_states[SDL_SCANCODE_A]) player.move(chunks, -0.2);
    if (key_states[SDL_SCANCODE_D]) player.move(chunks, 0.2);
}
