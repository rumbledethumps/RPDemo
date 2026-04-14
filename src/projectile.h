#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdbool.h>
#include <stdint.h>

#define PLAYER_PROJECTILE_FRAME 0
#define ENEMY_PROJECTILE_FRAME  1
#define PICKUP_ENERGY_FRAME     2
#define PICKUP_SPEED_FRAME      3
#define PICKUP_POWER_FRAME      4
#define ASTEROID_FRAME_0        5
#define ASTEROID_FRAME_1        6
#define ASTEROID_FRAME_2        7
#define EXPLOSION_FRAME_0      10
#define EXPLOSION_FRAME_1      11
#define EXPLOSION_FRAME_2      12

#define FIRST_ENEMY_PROJECTILE_SLOT MAX_PLAYER_PROJECTILES

void projectile_init(void);
void projectile_fire_player(int16_t x, int16_t y);
bool projectile_fire_enemy(int16_t x, int16_t y, int16_t vx_q8, int16_t vy_q8, uint8_t frame_index);
bool projectile_spawn_explosion(int16_t x, int16_t y);
void projectile_spawn_asteroid_wave(uint8_t count);
bool projectile_hit_test_enemy(int16_t x, int16_t y, int16_t width, int16_t height);
bool projectile_hit_test_player(int16_t x, int16_t y, int16_t width, int16_t height);
void projectile_update(void);

#endif // PROJECTILE_H
