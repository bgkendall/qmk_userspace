ifeq ($(strip $(ENCODER_ENABLE)), yes)
    ifneq ($(strip $(VIAL_ENABLE)), yes)
        $(info Enabling BGK Encoder)
        SRC += bgk_encoder.c
    endif
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
    $(info Enabling BGK RGB)
    SRC += bgk_rgb.c
endif

ifeq ($(strip $(BGK_CUSTOM_WS2812_ENABLE)), yes)
    $(info Enabling BGK WS2812)
    SRC += bgk_ws2812_driver_init.c bgk_ws2812_driver.c
    CFLAGS += -DBGK_CUSTOM_WS2812_ENABLE -DRGB_MATRIX_DISABLE_KEYCODES
endif

ifeq ($(strip $(BGK_SHIFTED_MOD_TAP_ENABLE)), yes)
    $(info Enabling BGK Shifted Mod-Tap)
    SRC += bgk_shifted_mod_tap.c
	CFLAGS += -DBGK_SHIFTED_MOD_TAP_ENABLE
endif

ifeq ($(strip $(OS_DETECTION_ENABLE)), yes)
    $(info Enabling BGK OS Detect)
    SRC += bgk_os_detect.c
endif

SRC += bgk_keycommands.c bgk_keycodes.c
