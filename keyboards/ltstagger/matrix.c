/*


Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include QMK_KEYBOARD_H

/*
 * This constant define not debouncing time in msecs, assuming eager_pr.
 *
 * On Ergodox matrix scan rate is relatively low, because of slow I2C.
 * Now it's only 317 scans/second, or about 3.15 msec/scan.
 * According to Cherry specs, debouncing time is 5 msec.
 *
 * However, some switches seem to have higher debouncing requirements, or
 * something else might be wrong. (Also, the scan speed has improved since
 * that comment was written.)
 */

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static matrix_row_t read_cols(uint8_t row);
static void         init_cols(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

static uint8_t mcp23018_reset_loop;
// static uint16_t mcp23018_reset_loop;

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

void matrix_init(void) {
  // initialize row and col

  mcp23018_status = init_mcp23018();

  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i]     = 0;
    raw_matrix[i] = 0;
  }

  debounce_init(MATRIX_ROWS);
  matrix_init_quantum();
}

void matrix_power_up(void) {
  mcp23018_status = init_mcp23018();

  unselect_rows();
  init_cols();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    matrix[i] = 0;
  }
}

// Reads and stores a row, returning
// whether a change occurred.
static inline bool store_raw_matrix_row(uint8_t index) {
  matrix_row_t temp = read_cols(index);
  if (raw_matrix[index] != temp) {
    raw_matrix[index] = temp;
    return true;
  }
  return false;
}

uint8_t matrix_scan(void) {
  if (mcp23018_status) {  // if there was an error
    if (++mcp23018_reset_loop == 0) {
      // if (++mcp23018_reset_loop >= 1300) {
      // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
      // this will be approx bit more frequent than once per second
      print("trying to reset mcp23018\n");
      mcp23018_status = init_mcp23018();
      if (mcp23018_status) {
        print("left side not responding\n");
      } else {
        print("left side attached\n");
      }
    }
  }

  bool changed = false;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    select_row(i);

    // we don't need a 30us delay anymore, because selecting a
    // left-hand row requires more than 30us for i2c.

    changed |= store_raw_matrix_row(i);

    unselect_rows();
  }

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
  matrix_scan_quantum();

  return 1;
}

bool matrix_is_modified(void)  // deprecated and evidently not called.
{
  return true;
}

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

void matrix_print(void) {
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row);
    print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += bitpop16(matrix[i]);
  }
  return count;
}

/* Row pin configuration
 *
 * Teensy
 * row: 0   1   2   3
 * pin: D4  C6  D7  E6
 *
 * MCP23018
 * row: 0   1   2   3
 * pin: B3  B2  B1  B0
 */
static void unselect_rows(void) {
 // no need to unselect on mcp23018, because the select step sets all
 // the other row bits high, and it's not changing to a different
 // direction

 // unselect on teensy
 // Hi-Z(DDR:0, PORT:0) to unselect
 DDRC  &= ~(1 << 6);
 PORTC &= ~(1 << 6);
 DDRD  &= ~(1 << 4 | 1 << 7);
 PORTD &= ~(1 << 4 | 1 << 7);
 DDRE  &= ~(1 << 6);
 PORTE &= ~(1 << 6);
}

static void select_row(uint8_t row) {
  // select on mcp23018
  if (mcp23018_status) {  // if there was an error
    // do nothing
  } else {
    // set active row low  : 0
    // set other rows hi-Z : 1
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, LTSTAGGER_I2C_TIMEOUT);     if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPIOB, LTSTAGGER_I2C_TIMEOUT);              if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(0xFF & ~(1 << row), LTSTAGGER_I2C_TIMEOUT); if (mcp23018_status) goto out;
    out:
    i2c_stop();
  }

  // select on teensy
  // Output low(DDR:1, PORT:0) to select
  switch (row) {
    case 0:
    DDRD |= (1 << 4);
    PORTD &= ~(1 << 4);
    break;
    case 1:
    DDRC |= (1 << 6);
    PORTC &= ~(1 << 6);
    break;
    case 2:
    DDRD |= (1 << 7);
    PORTD &= ~(1 << 7);
    break;
    case 4:
    DDRE |= (1 << 6);
    PORTE &= ~(1 << 6);
    break;
  }
}

static matrix_row_t read_cols(uint8_t row) {
  uint8_t data    = 0;
  if (mcp23018_status) {  // if there was an error
    return 0;
  } else {
    // reading GPIOB (column port) since in mcp23018's sequential mode
    // it is addressed directly after writing to GPIOA in select_row()
    mcp23018_status = i2c_start(I2C_ADDR_READ, LTSTAGGER_I2C_TIMEOUT); if (mcp23018_status) goto out;
    mcp23018_status = i2c_read_nack(LTSTAGGER_I2C_TIMEOUT);            if (mcp23018_status < 0) goto out;
    data            = ~((uint8_t)mcp23018_status >> 1);
    mcp23018_status = I2C_STATUS_SUCCESS;
  out:
    i2c_stop();
  }

  /* read from teensy
   * bit mask is 'complex'
   */

  return data | (~(      ((PINF & 0xC0) >> 6)
                       | ((PINB & 0x01) << 2)
                       |  (PINB & 0x08)
                       | ((PINB & 0x04) << 2)
                       | ((PINB & 0x80) >> 1)
                  ));

}

/* Col pin configuration
 *
 * Teensy
 * col: 6   7   8   9   10  11
 * pin: F6  F7  B1  B3  B2  B6
 *
 * MCP23018
 * col: 0   1   2   3   4   5
 * pin: A1  A2  A3  A4  A5  A6
 */
 static void init_cols(void) {
   // init on mcp23018
   // not needed, already done as part of init_mcp23018()

   // init on teensy
   // Input with pull-up(DDR:0, PORT:1)
   DDRB &= ~(1 << 1 | 1 << 3 | 1 << 2 | 1 << 6);
   PORTB |= (1 << 1 | 1 << 3 | 1 << 2 | 1 << 6);
   DDRF &= ~(1 << 6 | 1 << 7);
   PORTF |= (1 << 6 | 1 << 7);
 }
