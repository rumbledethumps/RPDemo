#include <rp6502.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "constants.h"
#include "sprite_mode5.h"
#include "tile_mode2.h"
#include "input.h"
#include "player_controller.h"
#include "music.h"
#include "projectile.h"
#include "enemy.h"
#include "score.h"
#include "gameplay.h"

static bool init_graphics(void)
{
    // 320×240 canvas
    int rc;
    rc = xreg_vga_canvas(1);
    if (rc < 0) {
        puts("Error: xreg_vga_canvas(1) failed");
        return false;
    }

    sprite_mode5_init();
    tile_mode2_init();
    sprite_mode5_init_projectiles();
    sprite_mode5_init_enemies();
    projectile_init();
    enemy_init();
    score_init();

    return true;
}

uint8_t vsync_last = 0;

static void print_xram_range(const char *label, unsigned start, unsigned size)
{
    unsigned end = start + size - 1u;
    printf("%-16s %04X-%04X (%u)\n", label, start, end, size);
}

static void print_overlap_warning(const char *label, unsigned start, unsigned size, unsigned guard_start, unsigned guard_size)
{
    unsigned end = start + size - 1u;
    unsigned guard_end = guard_start + guard_size - 1u;

    if (!(end < guard_start || start > guard_end)) {
        printf("WARNING overlap: %s with %04X-%04X\n", label, guard_start, guard_end);
    }
}

static void dump_xram_layout(void)
{
    const unsigned mode2_cfg_size = (unsigned)sizeof(vga_mode2_config_t);
    const unsigned mode5_cfg_size = (unsigned)sizeof(vga_mode5_sprite_t);
    const unsigned player_cfg_size = mode5_cfg_size;
    const unsigned projectile_cfg_size = (unsigned)(MAX_PROJECTILES * mode5_cfg_size);
    const unsigned player_bullet_cfg_size = (unsigned)(MAX_PLAYER_PROJECTILES * mode5_cfg_size);
    const unsigned enemy_bullet_cfg_size = projectile_cfg_size - player_bullet_cfg_size;
    const unsigned enemy_cfg_size = (unsigned)(MAX_ENEMIES * mode5_cfg_size);

    puts("XRAM layout:");
    print_xram_range("SPRITE_DATA", SPRITE_DATA_START, SPRITE_DATA_END - SPRITE_DATA_START);
    print_xram_range("TILE_BG_CONFIG", TILE_BG_CONFIG, mode2_cfg_size);
    print_xram_range("TILE_FG_CONFIG", TILE_FG_CONFIG, mode2_cfg_size);
    print_xram_range("TILE_HUD_CONFIG", TILE_HUD_CONFIG, mode2_cfg_size);
    print_xram_range("PLAYER_CONFIG", PLAYER_CONFIG, player_cfg_size);
    print_xram_range("PROJ_CONFIG", PROJECTILE_CONFIG, projectile_cfg_size);
    print_xram_range("PLAYER_BULLETS", PROJECTILE_CONFIG, player_bullet_cfg_size);
    print_xram_range("ENEMY_BULLETS", PROJECTILE_CONFIG + player_bullet_cfg_size, enemy_bullet_cfg_size);
    print_xram_range("ENEMY_CONFIG", ENEMY_CONFIG, enemy_cfg_size);
    print_xram_range("GAMEPAD_INPUT", GAMEPAD_INPUT, 40u);
    print_xram_range("KEYBOARD_INPUT", KEYBOARD_INPUT, 32u);

    print_overlap_warning("PLAYER_CONFIG", PLAYER_CONFIG, player_cfg_size, GAMEPAD_INPUT, 40u);
    print_overlap_warning("PROJ_CONFIG", PROJECTILE_CONFIG, projectile_cfg_size, GAMEPAD_INPUT, 40u);
    print_overlap_warning("ENEMY_CONFIG", ENEMY_CONFIG, enemy_cfg_size, GAMEPAD_INPUT, 40u);
    print_overlap_warning("PLAYER_CONFIG", PLAYER_CONFIG, player_cfg_size, KEYBOARD_INPUT, 32u);
    print_overlap_warning("PROJ_CONFIG", PROJECTILE_CONFIG, projectile_cfg_size, KEYBOARD_INPUT, 32u);
    print_overlap_warning("ENEMY_CONFIG", ENEMY_CONFIG, enemy_cfg_size, KEYBOARD_INPUT, 32u);
}

int main(void)
{

    // Initialize input
    xreg(0, 0, 0, KEYBOARD_INPUT);
    xreg(0, 0, 2, GAMEPAD_INPUT);

    // Initialise graphics
    if (!init_graphics()) {
        puts("Fatal: graphics initialization failed");
        return 1;
    }
    dump_xram_layout();
    music_init();
    init_input_system();
    player_controller_init();
    gameplay_init();

    // Main loop
    while (true) {
        // 1. SYNC
        if (RIA.vsync == vsync_last) continue;
        vsync_last = RIA.vsync;

        // 2. INPUT
        handle_input();

        gameplay_frame(is_action_pressed(0, ACTION_BTN_START));
    }

    return 0;
}