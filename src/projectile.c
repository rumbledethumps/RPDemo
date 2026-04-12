#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "projectile.h"
#include "sprite_mode5.h"

typedef struct {
    bool    active;
    int16_t x;
    int16_t y;
} Projectile;

static Projectile projectiles[MAX_PROJECTILES];

void projectile_init(void)
{
    for (uint8_t i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].active = false;
        projectiles[i].x = -32;
        projectiles[i].y = -32;
    }
    // Hardware slots are already positioned off-screen by sprite_mode5_init_projectiles()
}

void projectile_fire_player(int16_t x, int16_t y)
{
    for (uint8_t i = 0; i < MAX_PLAYER_PROJECTILES; i++) {
        if (!projectiles[i].active) {
            projectiles[i].active = true;
            projectiles[i].x = x;
            projectiles[i].y = y;
            sprite_mode5_set_projectile_position(i, x, y);
            return;
        }
    }
    // All player slots full — no-op
}

void projectile_update(void)
{
    for (uint8_t i = 0; i < MAX_PLAYER_PROJECTILES; i++) {
        if (!projectiles[i].active) continue;

        projectiles[i].y -= PROJECTILE_SPEED_PX;

        if (projectiles[i].y < HUD_TOP_PX) {
            // Bullet has left the play area — deactivate
            projectiles[i].active = false;
            sprite_mode5_set_projectile_position(i, -32, -32);
        } else {
            sprite_mode5_set_projectile_position(i, projectiles[i].x, projectiles[i].y);
        }
    }
}
