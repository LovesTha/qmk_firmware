#include "satan.h"

#define DISABLE_SPACE_CADET_ROLLOVER
#define PERMISSIVE_HOLD

//Tap Dance Declarations
enum {
  TD_Y_END = 0,
  TD_H_HOME,
  TD_UP_MENU,
  TD_GV_ESC
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_Y_END]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, KC_END),
  [TD_H_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_HOME),
  [TD_UP_MENU] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_MENU),
  [TD_GV_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_GRV)
};

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _WORLD 1
#define _SPC 2
#define _TAB 3

// dual-role shortcuts
#define TABDUAL   LT(_TAB, KC_TAB)
#define CAPSDUAL  CTL_T(KC_ESC)
#define SPACEDUAL LT(_SPC, KC_SPACE)
#define ENTERDUAL CTL_T(KC_ENT)
#define SLASHDUAL LT(_WORLD, KC_BSLS)
#define DWN_WKSPC LCTL(LALT(KC_DOWN))
#define UP_WKSPC LCTL(LALT(KC_UP))

#define KC_KP_00   M(0)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-----------------------------------------------------------.
   * |Esc~| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |
   * |-----------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|<-Y|  U|  I|  O|  P|  [|  ]|  \  |
   * |-----------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|->M|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|
   * |Shift/( |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |
   * |-----------------------------------------------------------|
   * |Ctrl|Gui |Alt |      Fn1/Space        |Alt |Gui |Menu|Ctrl |
   * `-----------------------------------------------------------'
   */
[_BL] = KEYMAP_ANSI(
  TD(TD_GV_ESC),     KC_1,    KC_2, KC_3, KC_4, KC_5,          KC_6, KC_7,    KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  TABDUAL,  KC_Q,    KC_W,    KC_E, KC_R, KC_T, TD(TD_Y_END),  KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, SLASHDUAL, \
  CAPSDUAL, KC_A,    KC_S,    KC_D, KC_F, KC_G, TD(TD_H_HOME), KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,          ENTERDUAL,  \
  KC_LSPO,  KC_Z,    KC_X,    KC_C, KC_V, KC_B, KC_N,          KC_M, KC_COMM, KC_DOT, KC_SLSH,   KC_RSPC, \
  KC_LCTL,  KC_LGUI, KC_LALT,                SPACEDUAL,            RALT_T(KC_PGUP), KC_RGUI, KC_MENU, RCTL_T(KC_PGDN)),

/* Keymap _SPC: Function Layer
   * ,-----------------------------------------------------------.
   * |PSc| F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|  DEL  |
   * |-----------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |Up |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |      |Left|Down|Rig|  |  |  |Left|Dow|Rgt|   |   | ToBase |
   * |-----------------------------------------------------------|
   * |        |Tk-|Paus|TK+|V+|V- |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |                        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_SPC] = KEYMAP_ANSI(
  KC_PSCR, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,   KC_DEL,  \
  KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_UP,   KC_TRNS, KC_TRNS, DWN_WKSPC, UP_WKSPC, KC_TRNS,\
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT,  KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,             TG(_SPC), \
  KC_TRNS, KC_TRNS, KC_APP,  KC_TRNS, KC_VOLU, KC_VOLD, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS),

  /* Keymap _TAB: Function Layer
   * ,-----------------------------------------------------------.
   * | ` |   |   |   |   |   |   | = | / | * | - |   |   |       |
   * |-----------------------------------------------------------|
   * |     |Hom|Up |End|   |   |   | 7 | 8 | 9 | + |   |   |     |
   * |-----------------------------------------------------------|
   * |      |Lft|Dwn|Rgh|   |   |   | 4 | 5 | 6 |Ent|   | ToBase |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   | 1 | 2 | 3 |Ent|          |
   * |-----------------------------------------------------------|
   * |    |    |    |                   0    | 00 | .  |    |    |
   * `-----------------------------------------------------------'
  */
[_TAB] = KEYMAP_ANSI(
  KC_TRNS, BL_DEC,  BL_INC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_EQUAL, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_TRNS, KC_TRNS, KC_TRNS,   \
  KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_TRNS,  KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_ENTER, KC_TRNS,          TG(_TAB), \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            KC_KP_0,                            KC_KP_00, KC_KP_DOT, KC_TRNS, KC_TRNS),

  /* Keymap _WORLD: Layer Navigation Layer
   * ,-----------------------------------------------------------.
   * | ` |   |   |   |   |   |   |   |   |   |   |   |   |  RESET|
   * |-----------------------------------------------------------|
   * |ToTAB|   |   |   |   |   |   |   |   |   |   |   |   |     |
   * |-----------------------------------------------------------|
   * |      |   |   |   |   |   |   |   |   |   |   |   | ToBase |
   * |-----------------------------------------------------------|
   * |        |   |   |   |   |   |   |   |   |   |   |          |
   * |-----------------------------------------------------------|
   * |    |    |    |         ToSpace        |    |    |    |    |
   * `-----------------------------------------------------------'
   */
[_WORLD] = KEYMAP_ANSI(
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   \
  TG(_TAB),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(_TAB),TG(_SPC), KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          TG(_BL), \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                            TG(_SPC),                           KC_M, KC_TRNS, KC_TRNS, KC_TRNS),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0: //a "00" key
                return MACRO( T(KP_0), T(KP_0), END );
        }
    }
    return MACRO_NONE;
};
