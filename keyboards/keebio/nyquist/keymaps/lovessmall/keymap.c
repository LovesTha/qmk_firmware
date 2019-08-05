#include "nyquist.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _NUMBER 3
#define _SYMBOL 4
#define _MACRO 5
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  NUMBER,
  SYMBOL,
  MACRO,
  ADJUST,
  EMAIL,
  NEWTAB,
  FINDALL,
  TRAINZ,
  TREB00T,
  TRELOAD,
  TFTS,
  TCPU,
  TICCISR,
  TICCRX,
  TICCTX,
  TRICCM,
  TRICCS,
  K1441,
  K4321,
  DETECT,
  PROGRM,
  REMISR,
  PLESS,
  ASSRT,
  TOLEFT,
  TORIGHT,
};

#define REPLACE LCTL(KC_EQUAL)


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_BSLASH, \
  KC_LCTL, KC_LALT, KC_LGUI, MACRO,   NUMBER,  LCTL_T(KC_ENT), KC_SPC, SYMBOL, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Number
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  _   |   +  |   =  |   -  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | Lock |   |  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  {   |  }   |  \   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home |scrnDn|scrnUp| End  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,     _______, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,          KC_0,        KC_DEL,  \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______, KC_LCBR, KC_RCBR,       KC_COLN,     _______, \
  _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,       _______,     KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_WBAK, KC_PGDN,       KC_PGUP,     KC_WFWD  \
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  _   |   +  |   =  |   -  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | Lock |   |  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  {   |  }   |  \   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home |scrnDn|scrnUp| End  |
 * `-----------------------------------------------------------------------------------'
 */
 [_SYMBOL] = LAYOUT( \
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,       _______,     _______, \
   KC_TILD, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9),       S(KC_0),     KC_DEL,  \
   _______, _______, _______, KC_BSLS, _______, KC_PGUP, KC_HOME, KC_PSCR, KC_LBRC, KC_RBRC,       KC_COLN,     KC_DQUO, \
   _______, _______, _______, KC_MINS, KC_EQL,  KC_PGDN, KC_END,  _______, KC_LABK, KC_RABK,       KC_QUES,     KC_PIPE, \
   _______, _______, _______, _______, _______, _______, _______, _______, TOLEFT , KC_PGDN,       KC_PGUP,     TORIGHT  \
),

/* Macro layer */
[_MACRO] = LAYOUT( \
   KC_NLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
   _______, KC_7   , KC_8   , KC_9   , TREB00T, NEWTAB , _______, _______, _______, _______, TRAINZ,  _______, \
   _______, KC_4   , KC_5   , KC_6   , FINDALL, _______, _______, _______, K1441  , PLESS  , _______, _______, \
   _______, KC_1   , KC_2   , KC_3   , _______, PROGRM , _______, _______, _______, _______, _______, KC_PIPE, \
   _______, KC_DOT , KC_0   , _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL, \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  KC_LCTL, KC_LALT, KC_LGUI, EMAIL,   NUMBER,  KC_SPC,  KC_SPC,  SYMBOL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_DEL, \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  KC_LCTL, KC_LALT, KC_LGUI, EMAIL,   NUMBER,  KC_SPC,  KC_SPC,  SYMBOL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
)


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case NUMBER:
      if (record->event.pressed) {
        layer_on(_NUMBER);
        update_tri_layer(_NUMBER, _SYMBOL, _ADJUST);
      } else {
        layer_off(_NUMBER);
        update_tri_layer(_NUMBER, _SYMBOL, _ADJUST);
      }
      return false;
      break;
    case SYMBOL:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
        update_tri_layer(_NUMBER, _SYMBOL, _ADJUST);
      } else {
        layer_off(_SYMBOL);
        update_tri_layer(_NUMBER, _SYMBOL, _ADJUST);
      }
      return false;
      break;
    case MACRO:
      if (record->event.pressed) {
        layer_on(_MACRO);
      } else {
        layer_off(_MACRO);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case EMAIL:
      if (record->event.pressed)
        SEND_STRING("gareth@cerberos.id.au");
      return false;
      break;
    case NEWTAB:
      if (record->event.pressed)
        SEND_STRING(SS_LCTRL("ctv\n"));
      return false;
      break;
    case TRAINZ:
      if (record->event.pressed)
        SEND_STRING("\npassword trainz\n");
      return false;
      break;
    case FINDALL:
      if (record->event.pressed)
        SEND_STRING( SS_LCTRL("F")SS_LALT("s") );
      return false;
      break;
    case TREB00T:
      if (record->event.pressed)
        SEND_STRING( "\npassword trainz\nreboot\n" );
      return false;
      break;
    case TRELOAD:
      if (record->event.pressed)
        SEND_STRING( "\npassword trainz\nreload\n" );
      return false;
      break;
    case TFTS:
      if (record->event.pressed)
        SEND_STRING( "\npassword trainz\nfts\n" );
      return false;
      break;
    case TCPU:
      if (record->event.pressed)
        SEND_STRING( "\ntrace cpu\n" );
      return false;
      break;
    case K4321:
      if (record->event.pressed)
        SEND_STRING( "\npassword trainz\nlocal key 4 3 2 1\n" );
      return false;
      break;
    case K1441:
      if (record->event.pressed)
        SEND_STRING( "\npassword trainz\nlocal key 14 41 a4 4a\n" );
      return false;
      break;
    case TICCISR:
      if (record->event.pressed)
        SEND_STRING( "\ntrace iccisr\n" );
      return false;
      break;
    case TICCTX:
      if (record->event.pressed)
        SEND_STRING( "\ntrace icctp\n" );
      return false;
      break;
    case TICCRX:
      if (record->event.pressed)
        SEND_STRING( "\ntrace iccrp\n" );
      return false;
      break;
    case DETECT:
      if (record->event.pressed)
        SEND_STRING( "\ntrace detector\n" );
      return false;
      break;
    case PROGRM:
      if (record->event.pressed)
        SEND_STRING( SS_LCTRL("p") );
        wait_ms(500);
        SEND_STRING( "\t\n" );
      return false;
      break;
    case REMISR:
      if (record->event.pressed)
        SEND_STRING( "q"SS_LCTRL("c")SS_TAP(X_UP)"\n" );
      return false;
      break;
    case PLESS:
      if (record->event.pressed)
        SEND_STRING( SS_LSFT("\\")"less\n" );
      return false;
      break;
    case TRICCM:
      if (record->event.pressed)
        SEND_STRING( "\ntrace icctp\n" );
      return false;
      break;
    case TRICCS:
      if (record->event.pressed)
        SEND_STRING( "\ntrace icc\ntrace iccisr\n" );
      return false;
      break;
    case TOLEFT:
      if (record->event.pressed)
        SEND_STRING( SS_LGUI( SS_LSFT( SS_TAP(X_LEFT) ) ) );
      return false;
      break;
    case TORIGHT:
      if (record->event.pressed)
        SEND_STRING( SS_LGUI( SS_LSFT( SS_TAP(X_RIGHT) ) ) );
      return false;
      break;
    case ASSRT:
      if (record->event.pressed)
        SEND_STRING( "/*lint -e{9034} */ assert( pBuf ); //Using the ASSERT that doesn't need the exception makes PCLint not see that we've checked for null pointers" );
      return false;
      break;
  }
  return true;
}
