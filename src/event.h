#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdbool.h>

#include "state.h"

void handle_events(bool *running, GameState *game_state);

#endif
