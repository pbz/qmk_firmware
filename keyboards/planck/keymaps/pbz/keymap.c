/* Copyright 2015-2017 Jack Humbert
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

// TODO: Handle sloppy layer exit

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _QWERTY_MR,
  _COLEMAK,
  _DVORAK,
  _PLOVER,
  _LOWER,
  _LOWER_MR,
  _RAISE,
  _RAISE_MR,
  _NUM,
  _NUM_MR,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  QWERTY_MR,
  COLEMAK,
  DVORAK,
  PLOVER,
  LOWER,
  LOWER_MR,
  RAISE,
  RAISE_MR,
  NUM,
  NUM_MR,
  BACKLIT,
  EXT_PLV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//TODO: Implemenent Mirrored layers for one handed use
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Num  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Ctrl | Alt  | GUI  |Lower |Sp/Mir|Sp/Ctl|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {MO(_NUM),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, LT(_NUM, KC_QUOT)},
  {MT(MOD_LSFT, KC_CAPSLOCK), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_ENT) },
  {KC_ESC, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   LT(_QWERTY_MR, KC_SPC),  MT(MOD_RGUI, KC_SPC),  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT} // Would be nice to have way to swap the two space keys for better right hand support
},

// Qwerty - Mirrored
[_QWERTY_MR] = {
  {KC_BSPC, KC_P,    KC_O,     KC_I,   KC_U,         KC_Y,   KC_T,    KC_R,    KC_E,   KC_W,   KC_Q,   KC_TAB},
  {KC_QUOT,  KC_SCLN,  KC_L  , KC_K   ,  KC_J  ,  KC_H  , KC_G   ,  KC_F  ,  KC_D  ,  KC_S  ,  KC_A  , TT(_NUM)},
  {MT(MOD_RSFT, KC_ENT), KC_SLSH,  KC_DOT  ,  KC_COMM  ,  KC_M  ,  KC_N  ,  KC_B  ,  KC_V  ,  KC_C  , KC_X, KC_Z ,  MT(MOD_LSFT, KC_CAPSLOCK)},
  {KC_RGHT, MT(MOD_RCTL, KC_UP), MT(MOD_RSFT, KC_DOWN), MT(MOD_RGUI, KC_LEFT), MO(_RAISE_MR),_______  , _______ , LOWER ,  KC_LGUI , KC_LALT, KC_LCTL, KC_ESC  }
},

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = {
  {KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = {
  {KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC},
  {KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH},
  {KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT },
  {BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

// TODO: Workman layout

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   6  |   7  |   8  |   9  |   0  |      |   -  |   =  |      |      |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   -  |   =  |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
  {_______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  _______, _______, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_QUESTION, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END}
},
// If we want our one-handed (mirrored) layout to only require 
[_RAISE_MR] = {
  {KC_DEL,  KC_0,  KC_9  ,  KC_8  ,  KC_7  ,  KC_6  , KC_5   ,  KC_4  ,  KC_3  ,  KC_2  , KC_1   , KC_GRV   },
  {_______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  _______, _______, KC_BSLS}, //TODO
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_QUESTION, _______}, //TODO
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END} //TODO
},


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   ^  |   &  |   *  |   (  |   )  |      |   _  |   +  |   [  |   ]  |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,             KC_RPRN,              KC_DEL },
  {_______, _______, _______, _______, _______, _______,       _______, KC_UNDS, KC_PLUS, KC_LBRC,             KC_RBRC,              KC_PIPE},
  {_______, _______, _______, _______, _______, _______,       _______, _______, _______, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, _______},
  {_______, _______, _______, _______, _______, MO(_LOWER_MR), _______, _______, _______,  _______,            _______,              _______}  
},

[_LOWER_MR] = {
  {KC_DEL, KC_RPRN, KC_LPRN, KC_ASTR  , KC_AMPR, KC_CIRC , KC_PERC, KC_DLR,  KC_HASH  ,  KC_AT  , KC_EXLM, KC_TILD},
  {_______, _______, _______, _______, _______, _______, _______,   KC_UNDS,    KC_PLUS,    KC_LBRC, KC_RBRC, KC_PIPE}, //TODO
  {_______, _______, _______, _______, _______, _______, _______,  _______, _______, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE,  _______}, //TODO
  {_______, _______, _______, _______, _______, _______, _______, _______,    _______,    KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET, _______} //TODO
},

/* Num
 * ,-----------------------------------------------------------------------------------.
 * |      |  7   |  8   |  9   |  *   |      |      |  7   |  8   |  9   |  *   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  4   |  5   |  6   |  /   |      |      |  4   |  5   |  6   |  /   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  1   |  2   |  3   |  +   |      |      |  1   |  2   |  3   |  +   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  0   |  .   | Enter|  -   |   =  |      |  0   |  .   | Enter|  -   |  =   |
 * `-----------------------------------------------------------------------------------'
 */
[_NUM] = {
  {_______, KC_KP_7, KC_KP_8,   KC_KP_9,     KC_KP_ASTERISK,     _______, _______, KC_KP_7, KC_KP_8, KC_KP_9,       KC_KP_ASTERISK,     _______},
  {_______, KC_KP_4, KC_KP_5,   KC_KP_6,     KC_KP_SLASH,        _______, _______, KC_KP_4, KC_KP_5, KC_KP_6,       KC_KP_SLASH,        _______},
  {_______, KC_KP_1, KC_KP_2,   KC_KP_3,     KC_KP_PLUS,         _______, _______, KC_KP_1, KC_KP_2, KC_KP_3,       KC_KP_PLUS,         _______},
  {_______, KC_KP_0, KC_KP_DOT, KC_KP_ENTER, KC_MINUS,       KC_KP_EQUAL, _______, KC_KP_0, KC_KP_DOT, KC_KP_ENTER, KC_MINUS,       KC_KP_EQUAL}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
}


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  dprintf("%u(%u)\n", keycode, biton32(layer_state));
  return true;
}
