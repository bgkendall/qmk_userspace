#include QMK_KEYBOARD_H

#ifdef CONSOLE_ENABLE
# include <print.h>
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS) && defined(RGBLIGHT_LAYER_BLINK)

#include "bgk_rgb.h"

const rgblight_segment_t* const PROGMEM clearpad_rgb_layers[] = RGBLIGHT_LAYERS_LIST
(
    bgkrgb_red_layer,
    bgkrgb_cyan_layer,
    bgkrgb_magenta_layer,
    bgkrgb_yellow_layer
);

void keyboard_post_init_kb(void)
{
# ifdef CONSOLE_ENABLE
# pragma message "CONSOLE ENABLED"
    // Enable/disable debugging:
    debug_enable = true;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;
#  endif

    // Set the LED layers:
    rgblight_layers = clearpad_rgb_layers;

    // Enable lighting subsystem, but don’t turn on any LEDs:
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_OFF);
}

layer_state_t layer_state_set_kb(layer_state_t state)
{
    uint8_t active_rgb_layer = get_highest_layer(state);
    rgblight_blink_layer(active_rgb_layer, 500);
    rgblight_unblink_all_but_layer(active_rgb_layer);

    return state;
}

#endif // ¬RGBLIGHT_ENABLE/RGBLIGHT_LAYERS/RGBLIGHT_LAYER_BLINK
