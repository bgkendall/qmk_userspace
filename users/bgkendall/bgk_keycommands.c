//
//  bgk_keycommands.c
//  qmk-keyboard
//
//  Created by Barnaby on 2021-08-01.
//  © 2021 Barnaby Kendall. All rights reserved.
//

#include "bgk_keycommands.h"

#include "quantum.h"


// Global variables and functions for Cmd+Tab via encoder or other non-standard mechanism.
// Adapted from https://docs.splitkb.com/hc/en-us/articles/360010513760
//
const uint16_t bgkey_command_tab_hold_time = 800; // ms
bool bgkey_is_command_tab_active = false;
uint16_t bgkey_command_tab_timer = 0;


bool is_windows(void)
{
// #ifdef OS_DETECTION_ENABLE
//     return (detected_host_os() == OS_LINUX ||
//             detected_host_os() == OS_WINDOWS);
// #else
//     return false;
// #endif
    if (keymap_config.swap_lctl_lgui)
    {
        return true;
    }
    else {
        return false;
    }
}

void bgkey_register_command_for_tab(void)
{
    if (!bgkey_is_command_tab_active)
    {
        // Register Command for Cmd+Tab handling:
        bgkey_is_command_tab_active = true;
        if (is_windows())
        {
            register_code(KC_LALT);
        }
        else
        {
            register_code(KC_LCMD);
        }
    }
    bgkey_command_tab_timer = timer_read();
}

bool bgkey_unregister_command_for_tab(bool immediate)
{
    if (bgkey_is_command_tab_active)
    {
        // Unregister Command after Cmd+Tab times out:
        if (immediate || timer_elapsed(bgkey_command_tab_timer) > bgkey_command_tab_hold_time)
        {
            bgkey_is_command_tab_active = false;
            if (is_windows())
            {
                unregister_code(KC_LALT);
            }
            else
            {
                unregister_code(KC_LCMD);
            }
        }
    }

    return false;
}

bool bgkey_register_forward_command_tab(void)
{
    bgkey_register_command_for_tab();
    if (is_windows())
    {
        tap_code16(KC_TAB);
    }
    else
    {
        tap_code16(BGKEY_FORWARD_TAB);
    }

    return false;
}

bool bgkey_register_backward_command_tab(void)
{
    bgkey_register_command_for_tab();
    if (is_windows())
    {
        tap_code16(S(KC_TAB));
    }
    else
    {
        tap_code16(BGKEY_BACKWARD_TAB);
    }

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state)
{
    if (state == 0)
    {
        bgkey_unregister_command_for_tab(true);
    }

    return state;
}



/*****************************************************************************
 * CAPS WORD                                                                 *
 *****************************************************************************/

#ifdef CAPS_WORD_ENABLE

#ifdef VIAL_TAP_DANCE_ENTRIES
#   define BGK_TAP_DANCE_ENTRIES VIAL_TAP_DANCE_ENTRIES
#else
#   define BGK_TAP_DANCE_ENTRIES 32
#endif

bool caps_word_press_user(uint16_t keycode)
{
    switch (keycode)
    {
        // Keycodes that continue Caps Word, with shift applied:
        case KC_A ... KC_Z:
        case KC_MINS:
        // The first 50% of Tap Dances will cancel Caps Word, the other half will be shifted:
        case (QK_TAP_DANCE + BGK_TAP_DANCE_ENTRIES/2) ... QK_TAP_DANCE_MAX:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key
            return true;

        // Keycodes that continue Caps Word, without shifting:
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word
    }
}

#endif // CAPS_WORD_ENABLE
