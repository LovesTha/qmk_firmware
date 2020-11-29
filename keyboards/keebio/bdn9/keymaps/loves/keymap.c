/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
#include QMK_KEYBOARD_H

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_UP,   RGB_MOD,
        KC_LEFT, KC_DOWN, KC_RIGHT,
        MO(1),   MO(2),   MO(3)
    ),
    [1] = LAYOUT(
        S(KC_1), S(KC_2), S(KC_3),
        S(KC_4), S(KC_5), S(KC_6),
        _______,  _______ , RESET
    ),
    [2] = LAYOUT(
        A(KC_1), A(KC_2), A(KC_3),
        A(KC_4), A(KC_5), A(KC_6),
        _______,  _______ , RESET
    ),
    [3] = LAYOUT(
        C(KC_1), C(KC_2), C(KC_3),
        C(KC_4), C(KC_5), C(KC_6),
        _______,  _______ , RESET
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
