#include QMK_KEYBOARD_H

uint16_t timer;

enum planck_keycodes {
  ADJUST = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(G(KC_F17), G(KC_F18), G(KC_F19),
               G(KC_F14), ADJUST, G(KC_F16),
               G(KC_F11), G(KC_F12), G(KC_F13)),

  [1] = LAYOUT(RGB_TOG, KC_TRNS, RESET,
               KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case ADJUST:
      if (record->event.pressed) {
        timer = timer_read();
        layer_on(1);
      } else {
        layer_off(1);
        if (timer_elapsed(timer) < 150) {
          tap_code16(G(KC_F15));
        }
      }
      return false;
  }
  return true;
}
