#include QMK_KEYBOARD_H


#define INDICATOR_PIN B2


#ifdef INDICATOR_PIN

const uint8_t os_indicator_flash_sequence[] =
{
    // Pseudo-Morse code to indicate OS type via single colour LED
    // Bytes are read right-to-left
    [OS_UNSURE]         = 0b11110101, // U . . —
    [OS_LINUX]          = 0b10101101, // L . – . .
    [OS_WINDOWS]        = 0b01010111, // D – . .
    [OS_MACOS...OS_IOS] = 0b01110111  // M — —
};

uint32_t flash_os_indicator(uint32_t trigger_time, void* cb_arg)
{
    uint8_t* os_indicator_sequence = (uint8_t*)cb_arg;

    // Set indicator pin based on LSB of current flash sequence state
    // Bit is flipped since LOW is ON and HIGH is OFF
    writePin(INDICATOR_PIN, !(*os_indicator_sequence & 1));

    if (*os_indicator_sequence)
    {
        *os_indicator_sequence >>= 1;
        return 333;
    }
    else
    {
        return 0;
    }
}

bool process_detected_host_os_kb(os_variant_t detected_os)
{
    static uint8_t os_indicator_sequence = 0;

    if (detected_os <= OS_IOS)
    {
        os_indicator_sequence = os_indicator_flash_sequence[detected_os];
        defer_exec(100, flash_os_indicator, (void*)&os_indicator_sequence);
    }

    return true;
}

#endif // INDICATOR_PIN

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    bool process = true;

    // Work-around for Layer-Tap only supporting basic key codes:
    if (record->event.pressed &&
        record->tap.count > 0 &&
        (keycode & QK_BASIC_MAX) == KC_WAKE)
    {
#       ifdef BACKLIGHT_ENABLE
        backlight_toggle();
#       endif
        process = false;
    }

    return process;
}

void keyboard_post_init_kb(void)
{
#   ifdef INDICATOR_PIN
    setPinOutput(INDICATOR_PIN); // Enable pin for front indicator light
    writePinHigh(INDICATOR_PIN); // Turn OFF front indicator light
#   endif
}
