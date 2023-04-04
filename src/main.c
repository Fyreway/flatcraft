#include <stdbool.h>

#include <SDL.h>

#include "state.h"

int main(void) {
    SdlState state = init();

    SDL_SetRenderDrawColor(state.rend, 100, 203, 255, 0);

    bool running = true;

    while (running) {
        SDL_RenderClear(state.rend);
        SDL_RenderPresent(state.rend);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT: running = false; break;
            }
        }
    }

    SDL_DestroyRenderer(state.rend);
    SDL_DestroyWindow(state.win);
    SDL_Quit();
}
