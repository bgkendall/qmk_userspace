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
         CW_TOGG,   KC_W,   KC_D,   KC_P,   KC_F,     KC_ESC,   KC_J,   KC_L,   KC_O,    KC_Y,   KC_BSPC,
         KC_CAPS,   KC_R,   KC_S,   KC_T,   KC_G,     KC_QUOT,  KC_M,   KC_N,   KC_E,    KC_I,   KC_U,
         KC_Z,      KC_X,   KC_C,   KC_V,   KC_B,     RGB_TOG,  KC_K,   KC_H,   KC_COMM, KC_DOT, QK_BOOT,
                       KC_LALT,KC_LGUI,      KC_SPACE,    KC_ENTER,       MO(1),   MO(2)
    ),

    [1] = LAYOUT_ortho(
         _______,  _______,  _______,  _______,  _______,   _______, _______,  KC_7,     KC_8,     KC_9,     KC_0,
         _______,  _______,  _______,  _______,  _______,   _______, _______,  KC_4,     KC_5,     KC_6,     _______,
         _______,  _______,  _______,  _______,  _______,   _______, _______,  KC_1,     KC_2,     KC_3,     _______,
                                       _______,  _______,            _______,  _______, _______
    ),

    [2] = LAYOUT_ortho(
         _______,  _______,  _______,  _______,  _______,   _______, _______,  _______,   _______,   _______,    _______,
         _______,  _______,  _______,  _______,  _______,   _______, KC_LEFT,  KC_DOWN,   KC_UP,     KC_LEFT,    _______,
         _______,  _______,  _______,  _______,  _______,   _______, _______,  _______,   _______,   _______,    _______,
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
    RGBS_MAC,
    RGBS_WINDOWS,
    RGBS_LINUX,
    RGBS_CAPSWORD,
    RGBS_CAPSLOCK,
    RGBS_POWERON,
    RGBS_LAYERS
};

const hsv_t bgk_hsv_states[] = {
    [RGBS_TRANS]    = { HSV_OFF },
    [RGBS_OFF]      = { HSV_OFF },
    [RGBS_MAC]      = { HSV_WHITE },
    [RGBS_WINDOWS]  = { HSV_BLUE },
    [RGBS_LINUX]    = { HSV_YELLOW },
    [RGBS_CAPSWORD] = { HSV_VIVIDPINK },
    [RGBS_CAPSLOCK] = { HSV_RED },
    [RGBS_POWERON]  = { HSV_GREEN },
    [RGBS_LAYERS+0] = { HSV_OFF },
    [RGBS_LAYERS+1] = { HSV_OFF },
    [RGBS_LAYERS+2] = { HSV_ORANGERED },
    [RGBS_LAYERS+3] = { HSV_CYAN },
    [RGBS_LAYERS+4] = { HSV_GREEN },
    [RGBS_LAYERS+5] = { HSV_MAGENTA },
    [RGBS_LAYERS+6] = { HSV_OFF },
    [RGBS_LAYERS+7] = { HSV_SPRINGGREEN }
};

const rgb_t bgk_rgb_states[] = {
    [RGBS_TRANS]    = { RGB_OFF },
    [RGBS_OFF]      = { RGB_OFF },
    [RGBS_MAC]      = { RGB_WHITE },
    [RGBS_WINDOWS]  = { RGB_BLUE },
    [RGBS_LINUX]    = { RGB_YELLOW },
    [RGBS_CAPSWORD] = { RGB_VIVIDPINK },
    [RGBS_CAPSLOCK] = { RGB_RED },
    [RGBS_POWERON]  = { RGB_GREEN },
    [RGBS_LAYERS+0] = { RGB_OFF },
    [RGBS_LAYERS+1] = { RGB_OFF },
    [RGBS_LAYERS+2] = { RGB_ORANGERED },
    [RGBS_LAYERS+3] = { RGB_CYAN },
    [RGBS_LAYERS+4] = { RGB_GREEN },
    [RGBS_LAYERS+5] = { RGB_MAGENTA },
    [RGBS_LAYERS+6] = { RGB_OFF },
    [RGBS_LAYERS+7] = { RGB_SPRINGGREEN }
};

#define POWER_UP_HUE_STEP (1 << 1)


void set_rgb_matrix_state(bool on)
{
    static bool is_state_overriden = false;
    static bool was_matrix_enabled = false;

if (on) print("> ON!"); else print("> OFF!");
printf(" is_state_overriden: %d", is_state_overriden);
printf(" was_matrix_enabled: %d\n", was_matrix_enabled);

    if (on)
    {
        if (!is_state_overriden)
        {
            was_matrix_enabled = rgb_matrix_is_enabled();
            is_state_overriden = true;
        }
        if (!rgb_matrix_is_enabled())
        {
            rgb_matrix_enable_noeeprom();
        }
    }
    else
    {
        rgb_matrix_reload_from_eeprom();
        is_state_overriden = false;
    }

if (on) print("< ON!"); else print("< OFF!");
printf(" is_state_overriden: %d", is_state_overriden);
printf(" was_matrix_enabled: %d\n", was_matrix_enabled);

}

rgb_t get_layer_rgb(uint8_t layer)
{
    rgb_t rgb = { RGB_OFF };

    if (layer <= 7)
    {
        rgb = bgk_rgb_states[RGBS_LAYERS+layer];
    }

    return rgb;
}

bool is_layer_indicated(layer_state_t state)
{
    rgb_t colour = get_layer_rgb(get_highest_layer(state));

    if (colour.r == 0 && colour.g == 0 && colour.b == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool led_update_kb(led_t led_state)
{
    if (led_state.caps_lock)
    {
        set_rgb_matrix_state(true);
    }
    return led_update_user(led_state);
}

layer_state_t layer_state_set_kb(layer_state_t state)
{
    if (is_layer_indicated(state))
    {
        set_rgb_matrix_state(true);
    }
    return layer_state_set_user(state);
}

void caps_word_set_user(bool active)
{
    if (active)
    {
        set_rgb_matrix_state(true);
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)
{
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max))
    {
        return false;
    }

    static bool powering_up = true;
    static bool is_state_overriden = false;

    uint8_t rgb_state = RGBS_TRANS;

    if (unlikely(powering_up))
    {
print("Powering up\n");
        static uint8_t os_indication_count = 255;
        os_indication_count--;

        switch (detected_host_os())
        {
            case OS_MACOS:
            case OS_IOS:
            {
                rgb_state = RGBS_MAC;
//                 hsv_t hsv = rgb_matrix_config.hsv;
//                 if (((hsv.h + POWER_UP_HUE_STEP) % 256) == bgk_hsv_states[RGBS_POWERON].h)
//                 {
//                     os_indication_count = 0;
//                 }
//                 else
//                 {
//                     hsv.h += POWER_UP_HUE_STEP;
//                     rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
//
//                     return true;
//                 }
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
            rgb_state = RGBS_OFF;
            powering_up = false;
        }
    }
    else if (host_keyboard_led_state().caps_lock)
    {
print("Caps lock\n");
        rgb_state = RGBS_CAPSLOCK;
    }
    else if (is_caps_word_on())
    {
print("Caps word\n");
        rgb_state = RGBS_CAPSWORD;
    }
    else if (is_layer_indicated(layer_state))
    {
print("Layer\n");
        rgb_state = RGBS_LAYERS+get_highest_layer(layer_state);
    }
    else if (is_state_overriden)
    {
print("Off\n");
        rgb_state = RGBS_OFF;
    }

    if (rgb_state == RGBS_TRANS)
    {
       return true;
    }
    else if (rgb_state == RGBS_OFF)
    {
print("Turning off\n");
        is_state_overriden = false;
        set_rgb_matrix_state(false);
        return false;
    }
    else
    {
        is_state_overriden = true;
printf("Setting colour %d\n", bgk_rgb_states[rgb_state].r);
        rgb_matrix_set_color_all(bgk_rgb_states[rgb_state].r,
                                 bgk_rgb_states[rgb_state].g,
                                 bgk_rgb_states[rgb_state].b);
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
    set_rgb_matrix_state(true);
#endif

    keyboard_post_init_user();
}
