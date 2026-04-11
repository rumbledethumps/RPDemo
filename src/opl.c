#include "opl.h"

#include <rp6502.h>

#include "constants.h"

static void opl_hw_write(uint8_t reg, uint8_t value) {
    RIA.addr1 = OPL_XRAM_ADDR + reg;
    RIA.rw1 = value;
}

void opl_config(uint8_t enable, uint16_t addr) {
    (void)enable;
    xreg(0, 1, 0x01, addr);
}

void opl_write(uint8_t reg, uint8_t value) {
    opl_hw_write(reg, value);
}

void opl_init(void) {
    uint16_t reg;

    for (reg = 1; reg <= 0xF5; ++reg) {
        opl_write((uint8_t)reg, 0x00);
    }

    opl_write(0x01, 0x20);
    opl_write(0xBD, 0x00);
}
