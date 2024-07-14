#pragma once

#include "quantum.h"

#ifdef KEYBOARD_bgkendall_ortho5x12_rev1
  #include "rev1.h"
#endif
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2
  #include "rev2.h"
#endif
#ifdef KEYBOARD_bgkendall_ortho5x12_rev2_miryoku
  #include "rev2_miryoku.h"
#endif
#ifdef KEYBOARD_bgkendall_ortho5x12_rev3
  #include "rev3.h"
#endif
#ifdef KEYBOARD_bgkendall_ortho5x12_rev4
  #include "rev4.h"
#endif

#include "users/bgkendall/bgk_keycodes.h"

#ifndef VIAL_ENABLE
#ifdef TAP_DANCE_ENABLE

enum TAP_DANCE_KEYCODES
{
    TD_CPCT = 0,
    TD_LRBR,
    TD_LRB2,
    TD_LRB3,
    TD_LRB4,
    TD_LRB5,
    TD_GESC,
    TD_QESC,
    TD_QUOT
};

#else

#define TD(k) KC_NO

#endif // TAP_DANCE_ENABLE

#endif // ¬VIAL_ENABLE
