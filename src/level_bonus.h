#ifndef LEVEL_BONUS_H
#define LEVEL_BONUS_H

#include <stdint.h>
#include <stdbool.h>

void level_bonus_reset(void);
void level_bonus_begin(uint8_t current_level);
void level_bonus_update(uint8_t *hud_health_last);
bool level_bonus_is_complete(void);

#endif
