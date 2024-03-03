/* Copyright 2023 Fabien Fellay
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

#pragma once

#include "quantum.h"

/* Layers list */
enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN
};

#ifdef STATUS_INDICATOR_KEYS

#    ifndef RGB_MATRIX_EFFECT_DEFAULT_ON
#        define RGB_MATRIX_EFFECT_DEFAULT_ON true
#    endif  // RGB_MATRIX_EFFECT_DEFAULT_ON

/* Indicators LEDs colors */
static const RGB rgb_on  = (RGB){RGB_WHITE};
static const RGB rgb_off = (RGB){RGB_OFF};

#endif  // STATUS_INDICATOR_KEYS

// Custom EEPROM structure
typedef union {
    uint32_t raw;
    struct PACKED {
        // Store the debug enable-disable state
        bool    debug_message_enable : 1;
#ifdef STATUS_INDICATOR_KEYS
        // States to enable-disable the rgb matrix effects while preserving the indicators
        bool    rgb_matrix_effect_enable : 1;
        uint8_t mode : 6;
        uint8_t value;
#endif  // STATUS_INDICATOR_KEYS
    };
} kb_config_t;

#ifndef NKRO_DEFAULT_ON
#    define NKRO_DEFAULT_ON false
#endif  // NKRO_DEFAULT_ON

#ifndef DEBUG_MESSAGE_DEFAULT_ON
#    define DEBUG_MESSAGE_DEFAULT_ON false
#endif  // DEBUG_MESSAGE_DEFAULT_ON
