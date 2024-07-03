#pragma once

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 12

/* Bootmagic reset key */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 11

#ifdef CONSOLE_ENABLE
#define DEBUG_ACTION
#endif

/* Save space */
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
//#define NO_ACTION_ONESHOT

/* custom encoder handling */
#define ENCODERS_CLOCKWISE_KEY      { {1,5} }
#define ENCODERS_ANTI_CLOCKWISE_KEY { {2,5} }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
//#define DEBOUNCING_DELAY 5

/* Use right-hand modifiers for LM() */
#define LAYER_MOD_USE_RIGHT

/* prevent stuck modifiers */
//#define PREVENT_STUCK_MODIFIERS

/* Don't hold tap-hold modifiers in roll-over scenarios */
//#define IGNORE_MOD_TAP_INTERRUPT
//#define PERMISSIVE_HOLD_PER_KEY

#define TAPPING_TERM 200

/* declare low power usage for iOS */
//#define USB_MAX_POWER_CONSUMPTION 100

#ifdef RGBLIGHT_ENABLE
#if BOOTLOADER_SIZE >= 10000 || ! defined CONSOLE_ENABLE
#   define RGBLIGHT_EFFECT_BREATHING
#   define RGBLIGHT_EFFECT_RAINBOW_MOOD
#   define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#   define RGBLIGHT_EFFECT_SNAKE
#   define RGBLIGHT_EFFECT_KNIGHT
#   define RGBLIGHT_EFFECT_CHRISTMAS
#   define RGBLIGHT_EFFECT_STATIC_GRADIENT
#   define RGBLIGHT_EFFECT_RGB_TEST
#   define RGBLIGHT_EFFECT_ALTERNATING
#   define RGBLIGHT_EFFECT_TWINKLE
#endif
#define RGBLIGHT_LED_COUNT 12
#define RGBLIGHT_HUE_STEP 2
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 22
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYER_BLINK

#define RGBLIGHT_LAYER_KEY {0,5}

#endif

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0001

/* key matrix pins                                                             Pro Micro pins */
#define MATRIX_ROW_PINS { D2, D7, B3, C6, E6, NO_PIN }                      // RX1, 6, 14, 5, 7, dummy row for encoder
#define MATRIX_COL_PINS { D3, B5, B6, B2, F7, B1, F4, D1, F5, D0, F6, D4 }  // TX0, 9, 10, 16, A0, 15, A3, 2, A2, 3, A1, 4

/* encoder pins and settings */
#define ENCODERS_PAD_A { D5 }                                               // TxLED
#define ENCODERS_PAD_B { B0 }                                               // RxLED

#define WS2812_DI_PIN B4                                                       // 8
