//
//  bgk_os_detect.c
//
//  © 2024 Barnaby Kendall
//

#include "bgk_os_detect.h"
#include "action.h"
#include "keycode_config.h"
#include "os_detection.h"
#include "rgblight.h"


bool bgk_is_windows(void)
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

struct bgk_os_rgb_layer_t bgk_os_rgb_layer = {
    .mac     = 0,
    .windows = 0,
    .linux   = 0,
    .other   = 0
};

#ifdef OS_DETECTION_ENABLE

bool process_detected_host_os_user(os_variant_t detected_os)
{
    uint8_t rgblayer = 0;

    switch (detected_os)
    {
        case OS_MACOS:
        case OS_IOS:
            keymap_config.swap_lctl_lgui = false;
            keymap_config.swap_rctl_rgui = false;
            rgblayer = bgk_os_rgb_layer.mac;
            break;
        case OS_WINDOWS:
            keymap_config.swap_lctl_lgui = true;
            keymap_config.swap_rctl_rgui = true;
            rgblayer = bgk_os_rgb_layer.windows;
            break;
        case OS_LINUX:
            keymap_config.swap_lctl_lgui = true;
            keymap_config.swap_rctl_rgui = true;
            rgblayer = bgk_os_rgb_layer.linux;
            break;
        default:
            rgblayer = bgk_os_rgb_layer.other;
            break;
    }

    if (rgblayer)
    {
#       ifdef RGBLIGHT_ENABLE
#           ifdef RGBLIGHT_LAYER_BLINK
                rgblight_blink_layer_repeat(rgblayer, 333, 2);
#           endif
#       endif
    }

    return true;
}
#endif // OS_DETECTION_ENABLE
