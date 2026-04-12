#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdbool.h>

typedef enum {
    GAME_STATE_TITLE,
    GAME_STATE_PLAYING,
    GAME_STATE_PAUSED,
} game_state_t;

typedef enum {
    GAME_TRANSITION_NONE,
    GAME_TRANSITION_START_GAME,
    GAME_TRANSITION_PAUSE_GAME,
    GAME_TRANSITION_UNPAUSE_GAME,
} game_transition_t;

void game_state_init(void);
game_state_t game_state_get(void);
game_transition_t game_state_handle_start_button(bool start_pressed);

#endif // GAME_STATE_H
