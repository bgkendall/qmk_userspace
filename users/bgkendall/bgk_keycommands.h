//
//  bgk_keycommands.h
//  qmk-keyboard
//
//  Created by Barnaby on 2021-08-01.
//  © 2021 Barnaby Kendall. All rights reserved.
//

#pragma once

#include "quantum.h"


// Command-Tab simulation
//
#ifndef BGKEY_FORWARD_TAB
#   define BGKEY_FORWARD_TAB KC_TAB
#endif
#ifndef BGKEY_BACKWARD_TAB
#   define BGKEY_BACKWARD_TAB KC_GRAVE
#endif

void bgkey_register_command_for_tab(void);

bool bgkey_unregister_command_for_tab(bool immediate);

bool bgkey_register_forward_command_tab(void);

bool bgkey_register_backward_command_tab(void);
