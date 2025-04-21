// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LT(1, KC_WAKE), MO(2),
        KC_SLEP,        KC_MUTE
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS,
        BL_BRTG, KC_TRNS
    ),
    [2] = LAYOUT(
          KC_CAPS, KC_TRNS,
          MO(3),   MO(4)
    ),
    [3] = LAYOUT(
          KC_NO,   KC_NO,
          KC_TRNS, QK_BOOT
    ),
    [4] = LAYOUT(
          KC_NO,   KC_NO,
          QK_BOOT, KC_TRNS
    ),
    [5 ... (DYNAMIC_KEYMAP_LAYER_COUNT - 1)] = LAYOUT(
          KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS
    )
};

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =
    {
        ENCODER_CCW_CW(KC_BRID, KC_BRIU),
        ENCODER_CCW_CW(KC_VOLD, KC_VOLU)
    },
    [1] =
    {
        ENCODER_CCW_CW(BL_DOWN, BL_UP  ),
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS)
    },
    [2] =
    {
        ENCODER_CCW_CW(KC_NO, KC_NO),
        ENCODER_CCW_CW(KC_NO, KC_NO)
    },
    [3 ... DYNAMIC_KEYMAP_LAYER_COUNT - 1] =
    {
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS),
        ENCODER_CCW_CW(KC_TRNS, KC_TRNS)
    }
};

#endif // ENCODER_MAP_ENABLE
