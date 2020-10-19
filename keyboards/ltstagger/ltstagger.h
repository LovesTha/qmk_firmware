/* Copyright 2020 Gareth Pye
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include "i2c_master.h"

// I2C aliases and register addresses (see "mcp23018.md", it would be awesome if this file existed in the repository)
#define I2C_ADDR        0b0100111
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern i2c_status_t mcp23018_status;
#define LTSTAGGER_I2C_TIMEOUT 1000

extern i2c_status_t mcp23018_status;
extern uint8_t init_mcp23018(void);

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    l00, l01, l02, l03, l04, l05,           r05, r04, r03, r02, r01, r00,   \
    l10, l11, l12, l13, l14, l15,           r15, r14, r13, r12, r11, r10,   \
    l20, l21, l22, l23, l24, l25,           r25, r24, r23, r22, r21, r20,   \
                   l33, l34, l35,           r35, r34, r33                   \
) { \
    { l00,   l01,   l02,   l03, l04, l05, r00,   r01,   r02,   r03, r04, r05}, \
    { l10,   l11,   l12,   l13, l14, l15, r10,   r11,   r12,   r13, r14, r15}, \
    { l20,   l21,   l22,   l23, l24, l25, r20,   r21,   r22,   r23, r24, r25}, \
    { KC_NO, KC_NO, KC_NO, l33, l34, l35, KC_NO, KC_NO, KC_NO, r33, r34, r35}  \
}
