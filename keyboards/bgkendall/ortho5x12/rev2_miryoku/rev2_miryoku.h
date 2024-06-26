#pragma once

#include "quantum.h"
#include "manna-harbour_miryoku.h"


#define LAYOUT_ortho_5x12( \
      K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011, \
      K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111, \
      K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211, \
      K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311, \
      K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011  }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111  }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211  }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311  }, \
    { K400,  K401,  K402,  KC_NO, K403,  K404,  K406,  K407,  K408,  K409,  K410,  K411  }  \
}


// Bug fix for Tap Dance codes within mod-hold definitions in Miryoko generated code:
#define KC_TD(k) KC_##k

#define QUOT TD_QUOT
