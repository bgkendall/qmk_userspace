#pragma once

#define VIAL_KEYBOARD_UID {0xE4, 0x0E, 0x1E, 0x3D, 0xE0, 0x97, 0x65, 0x65}

#define VIAL_UNLOCK_COMBO_ROWS { 0,  0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#if defined BOOTLOADER_SIZE && BOOTLOADER_SIZE < 10000

#   undef  DYNAMIC_KEYMAP_LAYER_COUNT
#   define DYNAMIC_KEYMAP_LAYER_COUNT 5
#   define DYNAMIC_KEYMAP_MACRO_COUNT 10
#   define VIAL_COMBO_ENTRIES 4
#   define VIAL_KEY_OVERRIDE_ENTRIES 9
#   define VIAL_TAP_DANCE_ENTRIES 3

// Reduce firmware size by removing unneeded animations:
#   undef RGBLIGHT_EFFECT_ALTERNATING
#   undef RGBLIGHT_EFFECT_CHRISTMAS
#   undef RGBLIGHT_EFFECT_RGB_TEST
#   undef RGBLIGHT_EFFECT_SNAKE
#   undef RGBLIGHT_EFFECT_TWINKLE

#endif // BOOTLOADER_SIZE < 10000
