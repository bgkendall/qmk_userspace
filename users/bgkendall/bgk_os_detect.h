//
//  bgk_os_detect.h
//
//  © 2024 Barnaby Kendall
//

#pragma once


#include "quantum.h"

struct bgk_os_rgb_layer_t
{
    uint8_t mac;
    uint8_t windows;
    uint8_t linux;
    uint8_t other;
};

extern struct bgk_os_rgb_layer_t bgk_os_rgb_layer;
