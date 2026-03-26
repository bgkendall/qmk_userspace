// Copyright 2023 sporkus
// SPDX-License-Identifier: GPL-2.0-or-later

#include "debug.h"
#include "keycodes.h"
#include "rgb_matrix.h"

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


#ifdef RGB_MATRIX_ENABLE

#include "color.h"
#include "users/bgkendall/bgk_rgb.h"

enum RGB_STATES
{
    RGBS_TRANS = 0,
    RGBS_OFF,
    RGBS_WINDOWS,
    RGBS_LINUX,
    RGBS_CAPSWORD,
    RGBS_CAPSLOCK,
    RGBS_POWERON
 };

const hsv_t bgk_hsv_states[] = {
    [RGBS_TRANS]    = { HSV_BLACK },
    [RGBS_OFF]      = { HSV_BLACK },
    [RGBS_WINDOWS]  = { HSV_BLUE },
    [RGBS_LINUX]    = { HSV_YELLOW },
    [RGBS_CAPSWORD] = { HSV_VIVIDPINK },
    [RGBS_CAPSLOCK] = { HSV_RED },
    [RGBS_POWERON]  = { HSV_GREEN }
};

#define POWER_UP_HUE_STEP (1 << 1)

bool rgb_matrix_indicators_kb(void)
{
    if (!rgb_matrix_indicators_user())
    {
        return false;
    }

    static bool powering_up = true;

    uint8_t rgb_state = RGBS_TRANS;

    if (unlikely(powering_up))
    {
        static uint8_t os_indication_count = 101;
        os_indication_count--;

        switch (detected_host_os())
        {
            case OS_MACOS:
            case OS_IOS:
            {
                hsv_t hsv = rgb_matrix_config.hsv;
                if (((hsv.h + POWER_UP_HUE_STEP) % 256) == bgk_hsv_states[RGBS_POWERON].h)
                {
                    os_indication_count = 0;
                }
                else
                {
                    hsv.h += POWER_UP_HUE_STEP;
                    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);

                    return true;
                }
                break;
            }
            case OS_WINDOWS:
                rgb_state = RGBS_WINDOWS;
                break;
            case OS_LINUX:
                rgb_state = RGBS_LINUX;
                break;
            default:
                rgb_state = RGBS_POWERON;
                break;
        }

        if (os_indication_count == 0)
        {
            powering_up = false;
            rgb_matrix_disable_noeeprom();
        }
    }
    else if (host_keyboard_led_state().caps_lock)
    {
        rgb_state = RGBS_CAPSLOCK;
    }
    else if (is_caps_word_on())
    {
        rgb_state = RGBS_CAPSWORD;
    }

    if (rgb_state == RGBS_TRANS)
    {
        return true;
    }
    else
    {
        rgb_matrix_sethsv_noeeprom(bgk_hsv_states[rgb_state].h,
                                   bgk_hsv_states[rgb_state].s,
                                   bgk_hsv_states[rgb_state].v);
        return false;
    }
}

#endif // RGB_MATRIX_ENABLE


/*****************************************************************************
 * KEYBOARD INIT                                                             *
 *****************************************************************************/

void keyboard_post_init_kb(void)
{
#ifdef CONSOLE_ENABLE
    // Enable/disable debugging:
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard = true;
    debug_mouse = false;
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(bgk_hsv_states[RGBS_POWERON].h,
                               bgk_hsv_states[RGBS_POWERON].s,
                               bgk_hsv_states[RGBS_POWERON].v);
#endif

    keyboard_post_init_user();
}
