#include "satan.h"

#define DISABLE_SPACE_CADET_ROLLOVER
#define PERMISSIVE_HOLD
// Used for SHIFT_ESC
#define MODS_CTRL_MASK  (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

//Tap Dance Declarations
enum {
  TD_E_END = 0,
  TD_H_HOME,
  TD_DOWN_MENU,
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_E_END]  = ACTION_TAP_DANCE_DOUBLE(KC_E, KC_END),
  [TD_H_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_HOME),
  [TD_DOWN_MENU] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_MENU)
// Other declarations would go here, separated by commas, if you have them
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _SPC 1
#define _TAB 2

// dual-role shortcuts
#define TABDUAL   LT(_TAB, KC_TAB)
#define CAPSDUAL  CTL_T(KC_ESC)
#define SPACEDUAL LT(_SPC, KC_SPACE)
#define ENTERDUAL CTL_T(KC_ENT)

#define KC_KP_00   M(0)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|EnD|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|HoM|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift/( |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Fn1/Space        |Alt |Gui |Menu|Ctrl |
   * `-----------------------------------------------------------'
   */
[_BL] = KEYMAP_ANSI(
  KC_GRV,   KC_1,    KC_2,    KC_3,         KC_4, KC_5, KC_6,          KC_7,     KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  TABDUAL,  KC_Q,    KC_W,    TD(TD_E_END), KC_R, KC_T, KC_Y,          KC_U,     KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
  CAPSDUAL, KC_A,    KC_S,    KC_D,         KC_F, KC_G, TD(TD_H_HOME), KC_J,     KC_K,    KC_L,   KC_SCLN, KC_QUOT,          ENTERDUAL,  \
  KC_LSPO,  KC_Z,    KC_X,    KC_C,         KC_V, KC_B, KC_N,          KC_M,     KC_COMM, KC_DOT, KC_SLSH,   KC_RSPC, \
  KC_LCTL,  KC_LGUI, KC_LALT,                    SPACEDUAL,            RALT_T(KC_PGUP), RGUI_T(KC_PGDN), TD(TD_DOWN_MENU), RCTL_T(KC_UP)),

/* Keymap _SPC: Function Layer
   * ,-----------------------------------------------------------.
   * |PSc| F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |Up |   |   |   |BL |Stay |
   * |-----------------------------------------------------------|
   * |      |Left|Down|Rig|  |  |  |Left|Dow|Right|  |  |        |
   * |-----------------------------------------------------------|
   * |        |Tk-|Puase|TK+|V+|V- |   |   |   |   |   |         |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_SPC] = KEYMAP_ANSI(
  KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  \
  KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_INS,  KC_TRNS, KC_TRNS, KC_TRNS, TO(_BL), TO(_SPC),\
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_APP,  KC_TRNS, KC_VOLU, KC_VOLD, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  /* Keymap _TAB: Function Layer
   * ,-----------------------------------------------------------.
   * |   |   |   |   |   |   |   | = | / | * | - |   |   |  RESET|
   * |-----------------------------------------------------------|
   * |     |Hom|Up |End|   |   |   | 7 | 8 | 9 | + |   |BL |Stay |
   * |-----------------------------------------------------------|
   * |      |Lft|Dwn|Rgh|   |   |   | 4 | 5 | 6 |Ent|   |        |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   | 1 | 2 | 3 |Ent|          |
   * |-----------------------------------------------------------|
   * |    |    |    |                   0    | 00 | .  |    |    |
   * `-----------------------------------------------------------'
   */
[_TAB] = KEYMAP_ANSI(
  KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_EQUAL, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_TRNS, KC_TRNS, RESET,   \
  KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_TRNS,  TO(_BL), TO(_TAB), \
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ENTER, KC_TRNS,          KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_KP_0,                            KC_KP_00, KC_KP_DOT, KC_TRNS, KC_TRNS),
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0: //a "00" key
                return MACRO( T(KP_0), T(KP_0), END );
        }
    }
    return MACRO_NONE;
};
