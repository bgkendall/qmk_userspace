#include QMK_KEYBOARD_H

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_LAYERS) && defined(RGBLIGHT_LAYER_BLINK)

#include "bgk_rgb.h"

const rgblight_segment_t* const PROGMEM clearpad_rgb_layers[] = RGBLIGHT_LAYERS_LIST
(
    bgkrgb_red_layer,
    bgkrgb_cyan_layer,
    bgkrgb_magenta_layer,
    bgkrgb_white_layer
);

void keyboard_post_init_kb(void)
{
    // Turn off lighting:
    rgblight_disable();

    // Enable the LED layers:
    rgblight_layers = clearpad_rgb_layers;
}

layer_state_t layer_state_set_kb(layer_state_t state)
{
    bgkrgb_blink_highest_layer(state, 0, 3);

    return state;
}

#else
#   pragma message "Lighting disabled!"
#endif
