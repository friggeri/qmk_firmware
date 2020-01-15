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

#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_french_osx.h"

// for some reason these aren't properly defined
#undef FR_AT
#define FR_AT KC_NUBS
#undef FR_LESS
#define FR_LESS KC_GRV
#undef FR_HASH
#define FR_HASH LSFT(FR_AT)
#undef FR_GRTR
#define FR_GRTR LSFT(FR_LESS)
#define DEG LSFT(FR_RPRN)

// open iTerm
#define TERM LCMD(FR_AT)

// go to spaces
#define SP1  LCMD(FR_AMP)
#define SP2  LCMD(FR_EACU)
#define SP3  LCMD(FR_QUOT)
#define SP4  LCMD(FR_APOS)

// full screen
#define K_FULL LCMD(LCTL(KC_F))

// screen capture
#define K_CAPF LCMD(LSFT(FR_3))
#define K_CAPR LCMD(LSFT(FR_4))

// open special character selector
#define K_CHAR LCMD(LCTL(KC_SPC))

// open one password
#define K_PASS LCMD(FR_GRV)

enum planck_layers {
  _BASE,
  _LOWER,
  _RAISE,
  _HOME,
  _ADJUST
};

enum planck_keycodes {
  HOME = SAFE_RANGE,
  LOWER,
  RAISE,
  LEFT_SH,
  RGHT_SH
};

uint16_t last_pressed = 0;
uint8_t pressed_alone = 0;
#define PRESSED_LSFT 0
#define PRESSED_RSFT 1
#define PRESSED_LOW  2
#define PRESSED_RAIS 3
#define PRESSED_HOME 4

#define DUAL_TIMEOUT 300

#define IS_LAST_PRESSED(x) (record->event.time - last_pressed < DUAL_TIMEOUT) && (pressed_alone & (1 << x))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_planck_grid(
    KC_TAB,  FR_A,    FR_Z,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  FR_Q,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    FR_M,    KC_ENT ,
    LEFT_SH, FR_W,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    FR_COMM, FR_SCLN, FR_COLN, KC_UP,   RGHT_SH,
    HOME,    KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   _______, KC_LEFT, KC_DOWN, KC_RGHT
),
[_LOWER] = LAYOUT_planck_grid(
    FR_AT,   FR_AMP,  FR_EACU, _______, _______, _______, FR_SECT, FR_EGRV, FR_EXLM, FR_CCED, FR_AGRV, _______,
    _______, _______, _______, _______, _______, _______, _______, FR_CIRC, FR_DLR,  _______, FR_MINS, _______,
    _______, FR_LESS, _______, _______, _______, _______, _______, FR_EQL,  FR_UGRV, FR_GRV,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_RAISE] = LAYOUT_planck_grid(
    FR_HASH, FR_1,    FR_2,    FR_3,    FR_4,    FR_5,    FR_6,    FR_7,    FR_8,    FR_9,    FR_0,    _______,
    _______, _______, _______, _______, _______, _______, _______, FR_UMLT, FR_ASTR, DEG,  FR_UNDS, _______,
    _______, FR_LESS, _______, _______, _______, _______, _______, FR_PLUS, FR_PERC, FR_PND,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_HOME] = LAYOUT_planck_grid(
    TERM,    _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12, _______,
    SP1,     SP2,     SP3,     SP4,     K_FULL,  _______, _______, _______, _______, _______, _______, K_PASS,
    _______, _______, _______, _______, _______, K_CAPF,  K_CAPR,  _______, _______, _______, KC_F2,   _______,
    _______, _______, _______, _______, _______, K_CHAR,  K_CHAR,  _______, _______, _______, KC_F1,   _______
),
[_ADJUST] = LAYOUT_planck_grid(
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______,   RESET,
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______,   _______,
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______,   _______,
  _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______, _______,   _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    pressed_alone = 0;
    last_pressed = record->event.time;

    switch(keycode) {
      case LEFT_SH:
        pressed_alone = (1 << PRESSED_LSFT);
        register_mods(MOD_BIT(KC_LSFT));
        return false;
      case RGHT_SH:
        pressed_alone = (1 << PRESSED_RSFT);
        register_mods(MOD_BIT(KC_RSFT));
        return false;
      case LOWER:
        pressed_alone = (1 << PRESSED_LOW);
        layer_on(_LOWER);
        return false;
      case RAISE:
        pressed_alone = (1 << PRESSED_RAIS);
        layer_on(_RAISE);
        return false;
      case HOME:
        pressed_alone = (1 << PRESSED_HOME);
        layer_on(_HOME);
        return false;
    }
  } else {
    switch(keycode) {
      case LEFT_SH:
        unregister_mods(MOD_BIT(KC_LSFT));
        if (IS_LAST_PRESSED(PRESSED_LSFT)) {
          if (IS_LAYER_ON(_RAISE)) {
            tap_code16(FR_LCBR);
          } else if (IS_LAYER_ON(_LOWER)) {
            tap_code16(FR_LBRC);
          } else {
            tap_code16(FR_LPRN);
          }
        }
        return false;
      case RGHT_SH:
        unregister_mods(MOD_BIT(KC_RSFT));
        if (IS_LAST_PRESSED(PRESSED_RSFT)) {
          if (IS_LAYER_ON(_RAISE)) {
            tap_code16(FR_RCBR);
          } else if (IS_LAYER_ON(_LOWER)) {
            tap_code16(FR_RBRC);
          } else {
            tap_code16(FR_RPRN);
          }
        }
        return false;
      case LOWER: 
        layer_off(_LOWER);
        if (IS_LAST_PRESSED(PRESSED_LOW)) {
          tap_code16(FR_QUOT);
        }
        return false;
      case RAISE: 
        layer_off(_RAISE);
        if (IS_LAST_PRESSED(PRESSED_RAIS)) {
          tap_code16(FR_APOS);
        }
        return false;
      case HOME:
        layer_off(_HOME);
        if (IS_LAST_PRESSED(PRESSED_HOME)) {
          tap_code16(KC_CAPS);
        }
        return false;
    }
  }
  return true;
}


void matrix_scan_user(void) {
}

void encoder_update(bool clockwise) {
}

void dip_switch_update_user(uint8_t index, bool active) {
}

bool music_mask_user(uint16_t keycode) {
  return true;
}