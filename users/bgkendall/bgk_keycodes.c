//
//  bgk_keycodes.c
//
//  © 2021 Barnaby Kendall
//

#include "bgk_keycodes.h"
#include "bgk_keycommands.h"
#include "bgk_os_detect.h"
#include "bgk_rgb.h"
#ifdef BGK_SHIFTED_MOD_TAP_ENABLE
#   include "bgk_shifted_mod_tap.h"
#endif


#ifndef DYNAMIC_KEYMAP_MACRO_COUNT
#  define BGK_MACRO_COUNT 16
#else
#  define BGK_MACRO_COUNT DYNAMIC_KEYMAP_MACRO_COUNT
#endif


__attribute__ ((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t* record)
{
    return true;
}


// Certain complex key codes are often needed in a location where a Mod-Tap is
// also desired and thus only a basic key code would normally be supported.
// The following rarely used keys are overridden to solve this:
//
//  * Again (KC_AGAIN) -> Redo (Cmd+Shift+Z / Ctrl+Shift+Z on Windows)
//  * Keypad Comma (KC_KP_COMMA) -> Curly close quote (Option-Shift-Right Bracket)
//  * Calculator (KC_CALC) -> Thousands (000)
//
// These can each be disabled with the setting BGK_NO_<key>_OVERRIDE
// E.g., `#define BGK_NO_KC_AGAIN_OVERRIDE`
//
bool override_basic_key(uint16_t keycode, keyrecord_t* record)
{
    bool process = true;

    if (record->tap.count > 0 &&
        (
#ifndef BGK_NO_KC_AGAIN_OVERRIDE
            (keycode & QK_BASIC_MAX) == KC_AGAIN ||
#endif
#ifndef BGK_NO_KC_KP_COMMA_OVERRIDE
            (keycode & QK_BASIC_MAX) == KC_KP_COMMA ||
#endif
#ifndef BGK_NO_KC_CALC_OVERRIDE
            (keycode & QK_BASIC_MAX) == KC_CALCULATOR ||
#endif
            0
        )
       )
    {
        uint16_t replacement = KC_NO;

        switch (keycode & QK_BASIC_MAX)
        {
            case KC_AGAIN:
            {
                if (bgk_is_windows())
                {
                    replacement = C(S(KC_Z));
                }
                else
                {
                    replacement = G(S(KC_Z));
                }
                break;
            }
            case KC_KP_COMMA:
            {
                replacement = LSA(KC_RIGHT_BRACKET);
                break;
            }
            case KC_CALCULATOR:
            {
                replacement = BK_000;
                break;
            }
            default:
                break;
        }

        if (replacement != KC_NO)
        {
            if (record->event.pressed)
            {
                if (replacement == BK_000)
                {
                    bgkey_000();
                }
                else
                {
                    register_code16(replacement);
                }
            }
            else
            {
                unregister_code16(replacement);
            }

            process = false;
        }
    }

    return process;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    bool process = process_record_keymap(keycode, record);

#ifdef KEY_OVERRIDE_ENABLE
    if (process)
    {
        process = process_key_override(keycode, record);
    }
#endif

#ifdef BGK_SHIFTED_MOD_TAP_ENABLE
    if (process)
    {
        process = bgk_process_shifted_mod_tap(keycode, record);
    }
#endif

    if (process)
    {
        process = override_basic_key(keycode, record);
    }

    if (process && record->event.pressed)
    {
        static bool cursor_vertical = false;

        switch (keycode)
        {
            case KC_PRINT_SCREEN:
            {
                if (bgk_is_windows())
                {
                    tap_code16(G(S(KC_S)));
                }
                else
                {
                    tap_code16(G(S(KC_4)));
                }
                process = false;
                break;
            }
            case QK_RGB_MATRIX_TOGGLE:
            {
#if defined(RGB_MATRIX_ENABLE)
                bgkrgb_matrix_toggle();
#endif
                process = false;
                break;
            }
            case QK_UNDERGLOW_TOGGLE:
            {
#if defined(RGBLIGHT_ENABLE)
                rgblight_toggle();
#endif
#if defined(RGB_MATRIX_ENABLE) && !defined(RGB_MATRIX_DISABLE_SHARED_KEYCODES)
                bgkrgb_matrix_toggle();
#endif
                process = false;
                break;
            }
            case BK_000:
            {
                process = bgkey_000();
                break;
            }
            case BK_APP_BACKWARD:
            {
                process = bgkey_register_backward_app_switch();
                break;
            }
            case BK_APP_FORWARD:
            {
                process = bgkey_register_forward_app_switch();
                break;
            }
            case BK_BGK:
            {
                process = bgkey_bgk();
                break;
            }
            case BK_TIMES:
            {
                process = bgkey_times();
                break;
            }
            case BK_THORN:
            {
                // Th
                process = bgkey_thorn();
                break;
            }
            case BK_UPDIR:
            {
                process = bgkey_updir();
                break;
            }
            case BK_ELEFT:
                // Encoder cursor left (down if flipped):
                tap_code16(cursor_vertical ? KC_DOWN : KC_LEFT);
                process = false;
                break;
            case BK_ERIGHT:
                // Encoder cursor right (up if flipped):
                tap_code16(cursor_vertical ? KC_UP : KC_RIGHT);
                process = false;
                break;
            case BK_EDOWN:
                // Encoder cursor down (left if flipped):
                tap_code16(cursor_vertical ? KC_LEFT : KC_DOWN);
                process = false;
                break;
            case BK_EUP:
                // Encoder cursor up (right if flipped):
                tap_code16(cursor_vertical ? KC_RIGHT : KC_UP);
                process = false;
                break;
            case BK_EFLIP:
                // Flip encoder cursor orientation:
                cursor_vertical = !cursor_vertical;
                process = false;
                break;
            default:
                break;
        }
    }
    else if (process && !record->event.pressed)
    {
        switch (keycode)
        {
            case BK_APP_BACKWARD:
            {
                process = bgkey_unregister_backward_app_switch();
                break;
            }
            case BK_APP_FORWARD:
            {
                process = bgkey_unregister_forward_app_switch();
                break;
            }
            default:
                break;
        }
    }

    return process;
}
