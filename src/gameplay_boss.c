#include <stdint.h>
#include <stdbool.h>

#include "constants.h"
#include "music.h"
#include "sprite_mode5.h"
#include "tile_mode2.h"
#include "gameplay_boss.h"

#define BOSS_SWAY_RANGE_PX 24
#define BOSS_SWAY_STEP_PX 1
#define BOSS_ANIM_STEP_FRAMES 24

static bool boss_active = false;
static int16_t boss_x = BOSS_START_X;
static int16_t boss_y = BOSS_START_Y;
static int8_t boss_vx = BOSS_SWAY_STEP_PX;
static uint8_t boss_anim_tick = 0;
static uint8_t boss_frame_set = BOSS_FRAME_SET_A_BASE;

void gameplay_boss_begin(gameplay_runtime_t *state)
{
    (void)state;
    boss_active = true;
    boss_x = BOSS_START_X;
    boss_y = BOSS_START_Y;
    boss_vx = BOSS_SWAY_STEP_PX;
    boss_anim_tick = 0;
    boss_frame_set = BOSS_FRAME_SET_A_BASE;
    music_set_track(BOSS_STAGE_MUSIC_TRACK);
    tile_mode2_set_boss_hud_visible(true);
    tile_mode2_set_boss_health(BOSS_MAX_HEALTH);
    sprite_mode5_show_boss(boss_x, boss_y, boss_frame_set);
}

void gameplay_boss_update(gameplay_runtime_t *state)
{
    (void)state;
    if (!boss_active) {
        return;
    }

    boss_x = (int16_t)(boss_x + boss_vx);
    if (boss_x <= (BOSS_START_X - BOSS_SWAY_RANGE_PX)) {
        boss_x = (BOSS_START_X - BOSS_SWAY_RANGE_PX);
        boss_vx = BOSS_SWAY_STEP_PX;
    } else if (boss_x >= (BOSS_START_X + BOSS_SWAY_RANGE_PX)) {
        boss_x = (BOSS_START_X + BOSS_SWAY_RANGE_PX);
        boss_vx = -BOSS_SWAY_STEP_PX;
    }

    boss_anim_tick = (uint8_t)(boss_anim_tick + 1);
    if (boss_anim_tick >= BOSS_ANIM_STEP_FRAMES) {
        boss_anim_tick = 0;
        if (boss_frame_set == BOSS_FRAME_SET_A_BASE) {
            boss_frame_set = BOSS_FRAME_SET_B_BASE;
        } else {
            boss_frame_set = BOSS_FRAME_SET_A_BASE;
        }
    }

    sprite_mode5_show_boss(boss_x, boss_y, boss_frame_set);
}

void gameplay_boss_reset(void)
{
    boss_active = false;
    boss_x = BOSS_START_X;
    boss_y = BOSS_START_Y;
    boss_vx = BOSS_SWAY_STEP_PX;
    boss_anim_tick = 0;
    boss_frame_set = BOSS_FRAME_SET_A_BASE;
    tile_mode2_set_boss_hud_visible(false);
    sprite_mode5_hide_boss();
}
