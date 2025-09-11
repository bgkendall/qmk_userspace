//
//  bgk_os_detect.h
//
//  © 2024 Barnaby Kendall
//

#pragma once


struct bgk_os_rgb_layer_t
{
    uint8_t mac;
    uint8_t windows;
    uint8_t linux;
    uint8_t other;
};

bool bgk_is_windows(void);

extern struct bgk_os_rgb_layer_t bgk_os_rgb_layer;
