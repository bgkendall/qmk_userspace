#include QMK_KEYBOARD_H


#ifdef CONSOLE_ENABLE
#include <print.h>
#endif


#define MAX_COUNTED_KEY (KC_F13 + 1)
#define COUNT_SLOTS (MAX_COUNTED_KEY*4)
#define PRINT_EVERY_N_KEYSTROKES 4
#define COUNTS_PER_LINE 35

extern uint8_t extract_mod_bits(uint16_t code);

uint16_t key_counter[] = { [0 ... (COUNT_SLOTS-1)] = 0 };

bool process_record_keymap(uint16_t keycode, keyrecord_t* record)
{
    if (record->event.pressed)
    {
        static uint16_t counter = 0;

        int16_t base_keycode = keycode;

        if (IS_QK_MODS(keycode)    ||
            IS_QK_MOD_TAP(keycode) ||
            IS_QK_LAYER_TAP(keycode))
        {
            base_keycode &= QK_BASIC_MAX;
        }

        if (base_keycode < MAX_COUNTED_KEY)
        {
            const uint8_t modifiers = get_mods();

            if ((modifiers & MOD_MASK_ALT) || (extract_mod_bits(keycode) & MOD_MASK_ALT))
            {
                key_counter[base_keycode + (MAX_COUNTED_KEY*3)]++;
            }
            else if ((modifiers & MOD_MASK_CTRL) || (extract_mod_bits(keycode) & MOD_MASK_CTRL) ||
                     (modifiers & MOD_MASK_GUI)  || (extract_mod_bits(keycode) & MOD_MASK_GUI))
            {
                key_counter[base_keycode + (MAX_COUNTED_KEY*2)]++;
            }
            else if ((modifiers & MOD_MASK_SHIFT) || (extract_mod_bits(keycode) & MOD_MASK_SHIFT))
            {
                key_counter[base_keycode + MAX_COUNTED_KEY]++;
            }
            else
            {
                key_counter[base_keycode]++;
            }

            if (counter % PRINT_EVERY_N_KEYSTROKES == 0)
            {
                char s[] = { [0 ... 256] = '\0' };

                uint16_t key_start = ((counter/PRINT_EVERY_N_KEYSTROKES) * COUNTS_PER_LINE);

                // printf("%i, %i, %i, %i, %i, %i\n", counter, key_start, (key_start + COUNTS_PER_LINE), (((key_start/MAX_COUNTED_KEY)+1) * MAX_COUNTED_KEY), MAX_COUNTED_KEY, COUNT_SLOTS);

                for (uint16_t i = key_start; i < (key_start + COUNTS_PER_LINE) &&
                                             i < (((key_start/MAX_COUNTED_KEY)+1) * MAX_COUNTED_KEY) &&
                                             i < COUNT_SLOTS; i++)
                {
                    if (i == key_start)
                    {
                        if (i >= MAX_COUNTED_KEY*3)
                        {
                            sprintf(s, "!"); // Alt/Option
                        }
                        else if (i >= MAX_COUNTED_KEY*2)
                        {
                            sprintf(s, "^"); // Control & GUI/Command
                        }
                        else if (i >= MAX_COUNTED_KEY)
                        {
                            sprintf(s, "+"); // Shift
                        }
                    }
                    sprintf(s, "%s,%02X=%i", s, (i % MAX_COUNTED_KEY), key_counter[i]);
                }

                if (s[0] != '\0')
                {
                    printf("%s\n", s);
                }
            }

            counter++;
            if (counter > PRINT_EVERY_N_KEYSTROKES * 16)
            {
                counter = 0;
                print("\n====\n");
            }
        }
    }

    return true;
}

#ifdef RGBLIGHT_LAYERS

#include "users/bgkendall/bgk_rgb.h"

const rgblight_segment_t PROGMEM ortho_5_12_ok_layer[] = RGBLIGHT_LAYER_SEGMENTS
(
    BGKRGB_RAINBOW_PIXEL(0),
    BGKRGB_RAINBOW_PIXEL(1),
    BGKRGB_RAINBOW_PIXEL(2),
    BGKRGB_RAINBOW_PIXEL(3),
    BGKRGB_RAINBOW_PIXEL(4),
    BGKRGB_RAINBOW_PIXEL(5),
    BGKRGB_RAINBOW_PIXEL(6),
    BGKRGB_RAINBOW_PIXEL(7),
    BGKRGB_RAINBOW_PIXEL(8),
    BGKRGB_RAINBOW_PIXEL(9),
    BGKRGB_RAINBOW_PIXEL(10),
    BGKRGB_RAINBOW_PIXEL(11)
);

#ifndef KEYBOARD_bgkendall_ortho5x12_rev2m

enum RGB_LAYERS
{
    RGBL_A = 0,
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
    RGBL_OK
};

const rgblight_segment_t* const PROGMEM ortho_5_12_rgb_layers[] = RGBLIGHT_LAYERS_LIST
(
    [RGBL_F] = bgkrgb_white_indicator_layer,
    [RGBL_R] = bgkrgb_red_indicator_layer,
    [RGBL_K] = bgkrgb_coral_indicator_layer,
    [RGBL_J] = bgkrgb_orangered_indicator_layer,
    [RGBL_O] = bgkrgb_orange_indicator_layer,
    [RGBL_N] = bgkrgb_goldenrod_indicator_layer,
    [RGBL_D] = bgkrgb_gold_indicator_layer,
    [RGBL_L] = bgkrgb_yellow_indicator_layer,
    [RGBL_H] = bgkrgb_chartreuse_indicator_layer,
    [RGBL_G] = bgkrgb_green_indicator_layer,
    [RGBL_S] = bgkrgb_springgreen_indicator_layer,
    [RGBL_Q] = bgkrgb_turquoise_indicator_layer,
    [RGBL_E] = bgkrgb_teal_indicator_layer,
    [RGBL_C] = bgkrgb_cyan_indicator_layer,
    [RGBL_A] = bgkrgb_azure_indicator_layer,
    [RGBL_B] = bgkrgb_blue_indicator_layer,
    [RGBL_I] = bgkrgb_purple_indicator_layer,
    [RGBL_M] = bgkrgb_magenta_indicator_layer,
    [RGBL_P] = bgkrgb_pink_indicator_layer,

    [RGBL_CAPSWORD] = bgkrgb_vividpink_indicator_layer,
    [RGBL_CAPSLOCK] = bgkrgb_red_indicator_layer,
    [RGBL_OK]       = bgkrgb_green_layer
);

uint8_t get_rgb_layer(layer_state_t state)
{
    return (uint8_t)(keymap_key_to_keycode(get_highest_layer(state), (keypos_t)RGBLIGHT_LAYER_KEY) - KC_A);
}

layer_state_t layer_state_set_kb(layer_state_t state)
{
    if (keymap_key_to_keycode(get_highest_layer(state), (keypos_t){3,4}) == RGB_TOG)
    {
        // Meta layer has RGB underglow controls, so only blink layer
        // indicator so that the lighting being selected can be seen clearly:
        bgkrgb_blink_layer(get_rgb_layer(state), RGBL_A, RGBL_S);
    }
    else
    {
        bgkrgb_set_all_layers(get_rgb_layer(state), RGBL_A, RGBL_S);
    }

    return layer_state_set_user(state);
}

layer_state_t default_layer_state_set_kb(layer_state_t state)
{
    rgblight_blink_layer(get_highest_layer(state), BGKRGB_BLINK_TIME);

    return default_layer_state_set_user(state);
}


bool led_update_kb(led_t led_state)
{
    rgblight_set_layer_state(RGBL_CAPSLOCK, led_state.caps_lock);

    return true;
}

void caps_word_set_user(bool active)
{
    rgblight_set_layer_state(RGBL_CAPSWORD, active);
}

#endif // ¬KEYBOARD_bgkendall_ortho5x12_rev2m

#endif // RGBLIGHT_LAYERS


#ifndef VIAL_ENABLE

#ifdef TAP_DANCE_ENABLE

void td_copy_cut_press(qk_tap_dance_state_t* state, void* user_data)
{
    if ((get_mods() & MOD_MASK_CG) && state->count == 2)
    {
        register_code(KC_X);
    }
    else
    {
        register_code(KC_C);
    }
}

void td_copy_cut_reset(qk_tap_dance_state_t* state, void* user_data)
{
    unregister_code(KC_C);

    if (state->count == 2)
    {
        unregister_code(KC_X);
    }
}


typedef enum
{
    TD_NONE = 0,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

td_state_t td_get_current_state(qk_tap_dance_state_t* td_state)
{
    td_state_t current_state = TD_UNKNOWN;

    if (td_state->count == 1)
    {
        if (td_state->interrupted || !td_state->pressed)
        {
            current_state = TD_SINGLE_TAP;
        }
        else
        {
            current_state = TD_SINGLE_HOLD;
        }
    }
    else if (td_state->count == 2)
    {
        if (td_state->interrupted)
        {
            current_state = TD_DOUBLE_SINGLE_TAP;
        }
        else if (td_state->pressed)
        {
            current_state = TD_DOUBLE_HOLD;
        }
        else
        {
            current_state = TD_DOUBLE_TAP;
        }
    }

    return current_state;
}

static td_state_t td_lrb_state[17];

void td_bracket_layer_finished(qk_tap_dance_state_t* td_state, void* user_data)
{
    uint8_t layer = (uint8_t)(uintptr_t)user_data;
    td_lrb_state[layer] = td_get_current_state(td_state);

    switch (td_lrb_state[layer])
    {
        case TD_SINGLE_TAP:
        {
            register_code(KC_LBRC);
            break;
        }
        case TD_SINGLE_HOLD:
        case TD_DOUBLE_HOLD:
        {
            layer_on(layer);
            break;
        }
        case TD_DOUBLE_TAP:
        {
            register_code(KC_RBRC);
            break;
        }
        case TD_DOUBLE_SINGLE_TAP:
        {
            tap_code(KC_LBRC);
            register_code(KC_LBRC);
            break;
        }
        default:
            break;
    }
}

void td_bracket_layer_reset(qk_tap_dance_state_t* td_state, void* user_data)
{
    uint8_t layer = (uint8_t)(uintptr_t)user_data;

    switch (td_lrb_state[layer])
    {
        case TD_SINGLE_TAP:
        {
            unregister_code(KC_LBRC);
            break;
        }
        case TD_SINGLE_HOLD:
        {
            layer_off(layer);
            break;
        }
        case TD_DOUBLE_TAP:
        {
            unregister_code(KC_RBRC);
            break;
        }
        case TD_DOUBLE_SINGLE_TAP:
        {
            unregister_code(KC_LBRC);
            break;
        }
        default:
            break;
    }

    td_lrb_state[layer] = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] =
{
    [TD_CPCT] = ACTION_TAP_DANCE_FN_ADVANCED(td_copy_cut_press, NULL, td_copy_cut_reset),
    [TD_LRBR] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_LRB2] = { .fn = { NULL, td_bracket_layer_finished, td_bracket_layer_reset}, .user_data = (void*)2, },
    [TD_LRB3] = { .fn = { NULL, td_bracket_layer_finished, td_bracket_layer_reset}, .user_data = (void*)3, },
    [TD_LRB4] = { .fn = { NULL, td_bracket_layer_finished, td_bracket_layer_reset}, .user_data = (void*)4, },
    [TD_LRB5] = { .fn = { NULL, td_bracket_layer_finished, td_bracket_layer_reset}, .user_data = (void*)5, },
    [TD_GESC] = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_ESC),
    [TD_QESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
    [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_GRAVE)
};

#endif // TAP_DANCE_ENABLE



#ifdef KEY_OVERRIDE_ENABLE

bool disabled = false;

// Use with suppressed_mods to clear the modifiers
// BEFORE the replacement key is sent.
bool flush_modifiers(bool key_down, void* context)
{
    send_keyboard_report();
    return true;
}

const key_override_t override_cmd_esc_grave = {
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2m
    .trigger            = LT(U_MEDIA,KC_ESC),
#else
    .trigger            = KC_ESC,
#endif
    .trigger_mods       = MOD_MASK_GUI,
    .negative_mod_mask  = MOD_MASK_ALT,
    .layers             = ~0,
    .suppressed_mods    = 0,
    .replacement        = KC_GRAVE,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_alt_esc_stab = {
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2m
    .trigger            = LT(U_MEDIA,KC_ESC),
#else
    .trigger            = KC_ESC,
#endif
    .trigger_mods       = MOD_MASK_ALT,
    .negative_mod_mask  = MOD_MASK_GUI,
    .layers             = ~0,
    .suppressed_mods    = 0,
    .replacement        = S(KC_TAB),
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_ctl_esc_grave = {
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2m
    .trigger            = LT(U_MEDIA,KC_ESC),
#else
    .trigger            = KC_ESC,
#endif
    .trigger_mods       = MOD_MASK_CTRL,
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_CTRL,
    .custom_action      = flush_modifiers,
    .replacement        = KC_GRAVE,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_sft_esc_tilde = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, S(KC_GRAVE));

const key_override_t override_backspace_delete = {
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2m
    .trigger            = LT(U_SYM,KC_BSPC),
#else
    .trigger            = KC_BSPC,
#endif
    .trigger_mods       = MOD_MASK_SHIFT,
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_SHIFT,
    .custom_action      = flush_modifiers,
    .replacement        = KC_DEL,
    .options            = ko_options_default,
    .enabled            = NULL
};

const key_override_t override_comma_semi = {
    .trigger            = KC_COMM,
    .trigger_mods       = MOD_MASK_SHIFT,
    .negative_mod_mask  = MOD_MASK_CTRL | MOD_BIT(KC_LALT),
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_SHIFT,
    .custom_action      = flush_modifiers,
    .replacement        = KC_SCLN,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_dot_colon = {
    .trigger            = KC_DOT,
    .trigger_mods       = MOD_MASK_SHIFT,
    .negative_mod_mask  = MOD_MASK_CTRL | MOD_BIT(KC_LALT),
    .layers             = ~0,
    .suppressed_mods    = 0,
    .replacement        = KC_COLN,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_comma_paren = {
    .trigger            = KC_COMM,
    .trigger_mods       = MOD_MASK_CTRL,
    .negative_mod_mask  = MOD_MASK_SHIFT | MOD_BIT(KC_LALT),
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_CTRL,
    .custom_action      = flush_modifiers,
    .replacement        = KC_LPRN,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_dot_paren = {
    .trigger            = KC_DOT,
    .trigger_mods       = MOD_MASK_CTRL,
    .negative_mod_mask  = MOD_MASK_SHIFT | MOD_BIT(KC_LALT),
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_CTRL,
    .custom_action      = flush_modifiers,
    .replacement        = KC_RPRN,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_comma_angle = {
    .trigger            = KC_COMM,
    .trigger_mods       = MOD_BIT(KC_LALT),
    .negative_mod_mask  = MOD_MASK_SHIFT | MOD_MASK_CTRL,
    .layers             = ~0,
    .suppressed_mods    = MOD_BIT(KC_LALT),
    .custom_action      = flush_modifiers,
    .replacement        = KC_LT,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_dot_angle = {
    .trigger            = KC_DOT,
    .trigger_mods       = MOD_BIT(KC_LALT),
    .negative_mod_mask  = MOD_MASK_SHIFT | MOD_MASK_CTRL,
    .layers             = ~0,
    .suppressed_mods    = MOD_BIT(KC_LALT),
    .custom_action      = flush_modifiers,
    .replacement        = KC_GT,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_comma_brace = {
    .trigger            = KC_COMM,
    .trigger_mods       = MOD_MASK_CTRL | MOD_BIT(KC_LALT),
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_CTRL | MOD_BIT(KC_LALT),
    .custom_action      = flush_modifiers,
    .replacement        = KC_LBRC,
    .options            = ko_options_default,
    .enabled            = NULL
};
const key_override_t override_dot_brace = {
    .trigger            = KC_DOT,
    .trigger_mods       = MOD_MASK_CTRL | MOD_BIT(KC_LALT),
    .layers             = ~0,
    .suppressed_mods    = MOD_MASK_CTRL | MOD_BIT(KC_LALT),
    .custom_action      = flush_modifiers,
    .replacement        = KC_RBRC,
    .options            = ko_options_default,
    .enabled            = NULL
};

// This globally defines all key overrides to be used
const key_override_t** key_overrides = (const key_override_t *[])
{
    &override_cmd_esc_grave,
    &override_alt_esc_stab,
    &override_ctl_esc_grave,
    &override_sft_esc_tilde,
    &override_backspace_delete,
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2m
    &override_comma_semi,
    &override_dot_colon,
    &override_comma_paren,
    &override_dot_paren,
    &override_comma_angle,
    &override_dot_angle,
    &override_comma_brace,
    &override_dot_brace,
#endif // KEYBOARD_bgkendall_ortho5x12_rev2m
    NULL // Terminate the array of overrides
};

#endif // KEY_OVERRIDE_ENABLE

#endif // ¬VIAL_ENABLE


#ifndef KEYBOARD_bgkendall_ortho5x12_rev2m

void keyboard_post_init_kb(void)
{
#ifdef CONSOLE_ENABLE
    // Enable/disable debugging:
    debug_enable = true;
    debug_matrix = false;
#endif

#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers:
    rgblight_layers = ortho_5_12_rgb_layers;

    // Turn off lighting:
    rgblight_disable();

    // Flash OK layer:
    rgblight_blink_layer(RGBL_OK, 800);
#endif

#ifdef ENCODER_GROUND_PIN
    setPinOutput(ENCODER_GROUND_PIN);
    writePinLow(ENCODER_GROUND_PIN);
#endif
}

#endif // ¬KEYBOARD_bgkendall_ortho5x12_rev2m
