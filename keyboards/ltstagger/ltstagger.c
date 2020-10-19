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

#include "ltstagger.h"

bool i2c_initialized = 0;
i2c_status_t mcp23018_status;

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    print("init_mcp23018\n");

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
        print("i2c initialized\n");
    }
    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, LTSTAGGER_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    print("i2c_start\n");
    mcp23018_status = i2c_write(IODIRA, LTSTAGGER_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    print("i2c_write 1\n");
    mcp23018_status = i2c_write(0b00000000, LTSTAGGER_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    print("i2c_write 2\n");
    mcp23018_status = i2c_write(0b00111111, LTSTAGGER_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    print("i2c_write 3\n");
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, LTSTAGGER_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, LTSTAGGER_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00000000, LTSTAGGER_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0b00111111, LTSTAGGER_I2C_TIMEOUT);        if (mcp23018_status) goto out;

out:
    i2c_stop();

#ifdef LEFT_LEDS
    if (!mcp23018_status) mcp23018_status = ergodox_left_leds_update();
#endif // LEFT_LEDS

    // SREG=sreg_prev;

    return mcp23018_status;
}
