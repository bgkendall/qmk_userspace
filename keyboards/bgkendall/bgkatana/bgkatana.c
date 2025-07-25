#include QMK_KEYBOARD_H

#include "quantum.h"

#ifdef CONSOLE_ENABLE
# include <print.h>
#endif


/*****************************************************************************
 * RGB                                                                       *
 *****************************************************************************/

enum RGB_LAYERS
{
    RGBL_OFF = 0,
    RGBL_A,
    RGBL_B,
    RGBL_C,
    RGBL_D,
    RGBL_E,
    RGBL_F,
    RGBL_G,
    RGBL_H,
    RGBL_I,
    RGBL_J,
    RGBL_K,
    RGBL_L,
    RGBL_M,
    RGBL_N,
    RGBL_O,
    RGBL_P,
    RGBL_Q,
    RGBL_R,
    RGBL_S,
    RGBL_CAPSWORD,
    RGBL_CAPSLOCK,
    RGBL_POWERON
 };

// const uint8_t LAYER_COLOUR[] =
// {
//     RGBL_OFF,
//     RGBL_OFF,
//     RGBL_J,
//     RGBL_H,
//     RGBL_G,
//     RGBL_C,
//     RGBL_M,
//     RGBL_S
// };

uint8_t get_rgb_layer(layer_state_t state)
{
#ifdef RGBLIGHT_LAYER_KEY
    uint16_t rgb_layer_key = keymap_key_to_keycode(get_highest_layer(state),
                                                   (keypos_t)RGBLIGHT_LAYER_KEY);

    if (rgb_layer_key >= KC_A && rgb_layer_key <= KC_S)
    {
        return (uint8_t)(rgb_layer_key - KC_A + 1);
    }
#else
    // const static uint8_t NUM_LAYER_COLOURS = sizeof(LAYER_COLOUR)/sizeof(LAYER_COLOUR[0]);
    // uint8_t layer = get_highest_layer(state);
    // if (layer < NUM_LAYER_COLOURS)
    // {
    //     return LAYER_COLOUR[layer];
    // }
#endif // RGBLIGHT_LAYER_KEY

    return 0;
}


#ifdef RGB_MATRIX_ENABLE

#include "color.h"
#include "users/bgkendall/bgk_rgb.h"

const hsv_t bgk_hsv_layers[] = {
    [RGBL_OFF] = { HSV_BLACK },

    [RGBL_F] = { HSV_WHITE },
    [RGBL_R] = { HSV_RED },
    [RGBL_K] = { HSV_CORAL },
    [RGBL_J] = { HSV_ORANGERED },
    [RGBL_O] = { HSV_ORANGE },
    [RGBL_N] = { HSV_GOLDENROD },
    [RGBL_D] = { HSV_GOLD },
    [RGBL_L] = { HSV_YELLOW },
    [RGBL_H] = { HSV_CHARTREUSE },
    [RGBL_G] = { HSV_GREEN },
    [RGBL_S] = { HSV_SPRINGGREEN },
    [RGBL_Q] = { HSV_TURQUOISE },
    [RGBL_E] = { HSV_TEAL },
    [RGBL_C] = { HSV_CYAN },
    [RGBL_A] = { HSV_AZURE },
    [RGBL_B] = { HSV_BLUE },
    [RGBL_I] = { HSV_PURPLE },
    [RGBL_M] = { HSV_MAGENTA },
    [RGBL_P] = { HSV_PINK },

    [RGBL_CAPSWORD] = { HSV_VIVIDPINK },
    [RGBL_CAPSLOCK] = { HSV_RED },
    [RGBL_POWERON]  = { HSV_GREEN }
};

#define POWER_UP_HUE_STEP (1 << 1)

bool rgb_matrix_indicators_kb(void)
{
    if (!rgb_matrix_indicators_user())
    {
        return false;
    }

    static bool powering_up = true;

    uint8_t rgb_layer = RGBL_OFF;

    if (unlikely(powering_up))
    {
        static uint8_t os_indication_count = 100;

        switch (detected_host_os())
        {
            case OS_MACOS:
            case OS_IOS:
            {
                hsv_t hsv = rgb_matrix_config.hsv;
                if (((hsv.h + POWER_UP_HUE_STEP) % 256) == bgk_hsv_layers[RGBL_POWERON].h)
                {
                    powering_up = false;
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
                rgb_layer = RGBL_B;
                break;
            case OS_LINUX:
                rgb_layer = RGBL_L;
                break;
            default:
                rgb_layer = RGBL_POWERON;
                break;
        }
        os_indication_count--;

        if (os_indication_count == 0)
        {
            powering_up = false;
        }
    }
    else if (host_keyboard_led_state().caps_lock)
    {
        rgb_layer = RGBL_CAPSLOCK;
    }
    else if (is_caps_word_on())
    {
        rgb_layer = RGBL_CAPSWORD;
    }
    else
    {
        rgb_layer = get_rgb_layer(layer_state);
    }

    rgb_matrix_sethsv_noeeprom(bgk_hsv_layers[rgb_layer].h,
                               bgk_hsv_layers[rgb_layer].s,
                               bgk_hsv_layers[rgb_layer].v);

    return true;
}

#endif // RGB_MATRIX_ENABLE


void keyboard_post_init_kb(void)
{
#ifdef CONSOLE_ENABLE
    // Enable/disable debugging:
    debug_enable = true;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;
#endif

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_sethsv_noeeprom(bgk_hsv_layers[RGBL_POWERON].h,
                               bgk_hsv_layers[RGBL_POWERON].s,
                               bgk_hsv_layers[RGBL_POWERON].v);
#endif
}
