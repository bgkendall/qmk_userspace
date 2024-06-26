#pragma once

#define VIAL_KEYBOARD_UID {0x0C, 0x19, 0x70, 0x25, 0x7C, 0xC1, 0x0B, 0x01}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#if defined BOOTLOADER_SIZE && BOOTLOADER_SIZE < 10000

#   define DYNAMIC_KEYMAP_MACRO_COUNT 4
#   define VIAL_KEY_OVERRIDE_ENTRIES 4
#   define VIAL_TAP_DANCE_ENTRIES 4

#endif // BOOTLOADER_SIZE < 10000

#define VIAL_ENCODER_DEFAULT { KC_PGDN, KC_PGUP, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, RGB_HUD, RGB_HUI, _______, _______ };
