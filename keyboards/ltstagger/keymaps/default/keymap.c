/* Copyright 2020 lovestha
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _NUMBER,
    _SYMBOL,
    _MACRO,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
      LALT_T(KC_TAB),  KC_Q,   KC_W,       KC_F,   KC_P,  KC_G,                 KC_J,   KC_L,       KC_U,   KC_Y, KC_SCLN, RALT_T(KC_BSPC),
      LSFT_T(KC_ESC),  KC_A,   KC_R,       KC_S,   KC_T,  KC_D,                 KC_H,   KC_N,       KC_E,   KC_I,    KC_O, RSFT_T(KC_QUOT),
      LCTL_T(KC_TILD), KC_Z,   KC_X,       KC_C,   KC_V,  KC_B,                 KC_K,   KC_M,    KC_COMM, KC_DOT, KC_SLSH, RCTL_T(KC_BSLASH),
      _______,      _______,_______, MO(_MACRO), KC_ENT, MO(_NUMBER),    MO(_SYMBOL), KC_SPC, MO(_MACRO), _______,_______,_______
    ),
    [_NUMBER] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,          KC_0,        KC_DEL,  \
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_LCBR, KC_RCBR,       KC_COLN,     _______, \
      _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,       _______,     KC_PIPE, \
                                 _______, _______, _______, _______, _______, _______, _______,_______,_______, _______,_______,_______  \
    ),
    [_SYMBOL] = LAYOUT( \
      KC_TILD, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9),       S(KC_0),     KC_DEL,  \
      _______, _______, _______, KC_BSLS, _______, KC_PGUP, KC_HOME, KC_PSCR, KC_LBRC, KC_RBRC,       KC_COLN,     KC_DQUO, \
      _______, _______, _______, KC_MINS, KC_EQL,  KC_PGDN, KC_END,  _______, KC_LABK, KC_RABK,       KC_QUES,     KC_PIPE, \
                                 _______, _______, _______, _______, _______, _______, _______,_______,_______, _______,_______,_______ \
   ),

   /* Macro layer */
   [_MACRO] = LAYOUT( \
      _______, KC_7   , KC_8   , KC_9   , _______, RESET,   _______, _______, _______, _______, _______, RESET, \
      _______, KC_4   , KC_5   , KC_6   , KC_DOT , _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, \
      _______, KC_1   , KC_2   , KC_3   , KC_0   , _______, _______, _______, KC_BTN1, KC_BTN2, KC_BTN3, KC_PIPE, \
                                 _______, _______, _______, _______, _______, _______, _______,_______,_______, _______,_______,_______  \
   )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down9:17
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif

    switch (keycode) {
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
