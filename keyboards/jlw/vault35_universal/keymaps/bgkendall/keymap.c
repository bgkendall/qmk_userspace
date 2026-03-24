// Copyright 2023 sporkus
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keycodes.h"
#include "keymap_us.h"

#include QMK_KEYBOARD_H

#define HM_A	LSFT_T(KC_A)
#define HM_S	LALT_T(KC_S)
#define HM_D	LGUI_T(KC_D)
#define HM_F	LCTL_T(KC_F)
#define HM_J	RCTL_T(KC_J)
#define HM_K	RGUI_T(KC_K)
#define HM_L	RALT_T(KC_L)
#define HM_Z	LSFT_T(KC_Z)
#define HM_SLSH	LSFT_T(KC_SLSH)
#define HM_QUOT	RSFT_T(KC_QUOT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2u_bars(
         KC_Q,   KC_W,   KC_D,   KC_P,   KC_F,     KC_ESC,   KC_J,   KC_L,   KC_O,    KC_Y,   KC_BSPC,
         KC_A,   KC_R,   KC_S,   KC_T,   KC_G,     KC_QUOT,  KC_M,   KC_N,   KC_E,    KC_I,   KC_U,
         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,     RGB_TOG,  KC_K,   KC_H,   KC_COMM, KC_DOT, KC_SLSH,
                     KC_LALT,KC_LGUI,      KC_SPACE,    KC_ENTER,       MO(1),   MO(2)
    ),

    [1] = LAYOUT_ortho(
         _______,  _______,  _______,  _______,  _______,   _______, _______,  KC_7,     KC_8,     KC_9,     KC_0,
         _______,  _______,  _______,  _______,  _______,   _______, _______,  KC_4,     KC_5,     KC_6,     _______,
         _______,  _______,  _______,  _______,  _______,   QK_BOOT, _______,  KC_1,     KC_2,     KC_3,     _______,
                                       _______,  _______,            _______,  _______, _______
    ),

    [2] = LAYOUT_ortho(
         _______,  _______,  _______,  _______,  _______,   _______, _______,  _______,   _______,   _______,    _______,
         _______,  _______,  _______,  _______,  _______,   _______, KC_LEFT,  KC_DOWN,   KC_UP,     KC_LEFT,    _______,
         _______,  _______,  _______,  _______,  _______,   QK_BOOT, _______,  _______,   _______,   _______,    _______,
                                       _______,  _______,            _______,  _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [2] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif


bool process_record_keymap(int16_t keycode, keyrecord_t* record)
{
    bool process = true;
    int16_t base_keycode = keycode;

    if (IS_QK_MODS(keycode)    ||
        IS_QK_MOD_TAP(keycode) ||
        IS_QK_LAYER_TAP(keycode))
    {
        base_keycode &= QK_BASIC_MAX;
    }

    if (keycode == KC_WWW_FAVORITES ||
        (record->tap.count > 0 && base_keycode == KC_WWW_FAVORITES))
    {
        if (!process_key_override(keycode, record))
        {
            // Key Override triggered - do not send the programmed key
        }
        else if (record->event.pressed)
        {
            register_code16(KC_QUESTION);
        }
        else
        {
            unregister_code16(KC_QUESTION);
        }
        process = false;
    }

    return process;
}
