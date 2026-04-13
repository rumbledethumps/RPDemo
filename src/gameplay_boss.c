#include <stdbool.h>

#include "constants.h"
#include "music.h"
#include "tile_mode2.h"
#include "gameplay_boss.h"

static bool boss_active = false;

void gameplay_boss_begin(gameplay_runtime_t *state)
{
    (void)state;
    boss_active = true;
    music_set_track(BOSS_STAGE_MUSIC_TRACK);
    tile_mode2_set_boss_hud_visible(true);
    tile_mode2_set_boss_health(BOSS_MAX_HEALTH);
}

void gameplay_boss_update(gameplay_runtime_t *state)
{
    (void)state;
    if (!boss_active) {
        return;
    }
}

void gameplay_boss_reset(void)
{
    boss_active = false;
    tile_mode2_set_boss_hud_visible(false);
}
