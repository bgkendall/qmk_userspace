/* Copyright 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x4(
    KC_P7,    KC_P8,    KC_P9,    KC_PMNS,
    KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,    KC_PENT,
    KC_P0,    KC_PDOT,  KC_SPC,   MO(1)
  ),
  [1] = LAYOUT_ortho_4x4(
    QK_BOOT,  KC_PAST,  KC_PSLS,  _______,
    BL_TOGG,  BL_DOWN,  BL_UP,    BL_STEP,
    RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,
    RGB_SAI,  RGB_SAD,  _______,  _______
  ),
  [2] = LAYOUT_ortho_4x4(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  ),
  [3] = LAYOUT_ortho_4x4(
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  )
};


/*****************************************************************************
 * SETUP LIGHTING LAYERS                                                     *
 *****************************************************************************/

#ifdef RGBLIGHT_LAYERS

#include "users/bgkendall/bgk_rgb.h"

const rgblight_segment_t* const PROGMEM bgk_rgb_layers[] = RGBLIGHT_LAYERS_LIST
(
    [0] = bgkrgb_cyan_layer,
    [1] = bgkrgb_magenta_layer,
    [2] = bgkrgb_gold_layer
);

void keyboard_post_init_kb(void)
{
    rgblight_layers = bgk_rgb_layers;
}

#endif // RGBLIGHT_LAYERS


/*****************************************************************************
 * ENABLE CUSTOM KEYS                                                        *
 *****************************************************************************/

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    bool process = true;

    if (process)
    {
        static int dot_mode = 0;

        switch (keycode)
        {
            case QK_KB_0:
                if (record->event.pressed)
                {
                    // Increment dot mode:
                    if ( (++dot_mode) > 2 ) { dot_mode = 0; }
                    rgblight_blink_layer(dot_mode, 250);
                }
                process = false;
                break;
            case KC_KP_DOT:
            case QK_TAP_DANCE+1:
                switch (dot_mode)
                {
                    case 0:
                        break;
                    case 1:
                        keycode = KC_COMMA;
                        break;
                    case 2:
                        keycode = KC_DOT;
                        break;
                    default:
                        dot_mode = 0;
                        break;
                }
                if (record->event.pressed)
                {
                    register_code16(keycode);
                }
                else
                {
                    unregister_code16(keycode);
                }
                process = false;
                break;
            default:
                break;
        }
    }

    return (process &= process_record_user(keycode, record));
}
