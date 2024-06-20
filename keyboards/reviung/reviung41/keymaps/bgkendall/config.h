#pragma once

#define VIAL_KEYBOARD_UID {0x40, 0x4E, 0xA1, 0x89, 0x23, 0x14, 0x82, 0x88}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }


#undef  MATRIX_ROWS
#define MATRIX_ROWS 8

#undef  MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { F4, F5, F6, F7, B1, B3, B2, B6 }


#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define ENABLE_COMPILE_KEYCODE
//#define IGNORE_MOD_TAP_INTERRUPT


#undef  RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS
#undef  RGBLIGHT_MAX_LAYERS
#define RGBLIGHT_MAX_LAYERS 25 //(DYNAMIC_KEYMAP_LAYER_COUNT + 3)
#undef  RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#undef  RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_INDICATOR RGBLIGHT_LED_COUNT-1,1
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM RGBLIGHT_LED_COUNT-1
#define RGBLIGHT_LAYER_KEY {4,6}

#define WS2812_TRST_US 80

#undef NO_DEBUG
