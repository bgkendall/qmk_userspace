#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _NUM,
    _META
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,     KC_Q,    KC_W,    KC_D,    KC_P,    KC_G,       KC_M,    KC_O,    KC_L,    KC_Y,    KC_BSPC,    KC_EQL,
    KC_LSFT,	KC_A,    KC_R,    KC_S,    KC_T,    KC_B,       KC_K,    KC_N,    KC_E,    KC_I,    KC_U,       KC_MINS,
                KC_Z,    KC_X,    KC_C,    KC_V,                         KC_H,    KC_F,    KC_COMM, KC_DOT,
                          MT(KC_LGUI, KC_TAB), LT(_FN, KC_SPC), LT(_NUM, KC_ENT), KC_NO),

  [_FN] = LAYOUT(
    KC_ESC,     KC_Q,    KC_W,    KC_D,    KC_P,    KC_G,       KC_M,    KC_O,    KC_L,    KC_Y,    KC_BSPC,    KC_EQL,
    KC_LSFT,	KC_A,    KC_R,    KC_S,    KC_T,    KC_B,       KC_K,    KC_N,    KC_E,    KC_I,    KC_U,       KC_MINS,
                KC_Z,    KC_X,    KC_C,    KC_V,                         KC_H,    KC_F,    KC_COMM, KC_DOT,
                          MT(KC_LGUI, KC_TAB), LT(_FN, KC_SPC), LT(_NUM, KC_ENT), KC_NO),

  [_NUM] = LAYOUT(
    KC_ESC,     KC_Q,    KC_W,    KC_D,    KC_P,    KC_G,       KC_M,    KC_O,    KC_L,    KC_Y,    KC_BSPC,    KC_EQL,
    KC_LSFT,	KC_A,    KC_R,    KC_S,    KC_T,    KC_B,       KC_K,    KC_N,    KC_E,    KC_I,    KC_U,       KC_MINS,
                KC_Z,    KC_X,    KC_C,    KC_V,                         KC_H,    KC_F,    KC_COMM, KC_DOT,
                          MT(KC_LGUI, KC_TAB), LT(_FN, KC_SPC), LT(_NUM, KC_ENT), KC_NO),

  [_META] = LAYOUT(
    KC_ESC,     KC_Q,    KC_W,    KC_D,    KC_P,    KC_G,       KC_M,    KC_O,    KC_L,    KC_Y,    KC_BSPC,    KC_EQL,
    KC_LSFT,	KC_A,    KC_R,    KC_S,    KC_T,    KC_B,       KC_K,    KC_N,    KC_E,    KC_I,    KC_U,       KC_MINS,
                KC_Z,    KC_X,    KC_C,    KC_V,                         KC_H,    KC_F,    KC_COMM, KC_DOT,
                          MT(KC_LGUI, KC_TAB), LT(_FN, KC_SPC), LT(_NUM, KC_ENT), KC_NO)
};
