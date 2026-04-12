#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdint.h>

// Frames between player shots (lower = faster fire rate)
#define PLAYER_FIRE_RATE 8

void projectile_init(void);
void projectile_fire_player(int16_t x, int16_t y);
void projectile_update(void);

#endif // PROJECTILE_H
