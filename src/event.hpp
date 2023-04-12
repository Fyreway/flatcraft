#ifndef __EVENT_H__
#define __EVENT_H__

#include "state.hpp"

namespace flat {
    void handle_events(bool &running, State &state);
}

#endif
