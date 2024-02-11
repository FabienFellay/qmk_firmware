/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

/* Key matrix pins */
#define MATRIX_ROW_PINS \
    { B5, B4, B3, A15, A14, A13 }
#define MATRIX_COL_PINS \
    { A10, A9, A8, B1, B0, A7, A6, A5, A4, A3, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN, NO_PIN }
#define NO_PIN_START 10
#define NO_PIN_NUM 10
#define CLR_REG_VAL 0x3FF

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 60
#define DRIVER_2_LED_TOTAL 49
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3

/* Enable caps-lock unconditional indicator LED */
#define CAPS_LOCK_LED_INDEX 60

/* Enable num-lock unconditional indicator LED */
#define NUM_LOCK_LED_INDEX 37

/* Enable scroll-lock unconditional indicator LED */
#define SCROLL_LOCK_LED_INDEX 14

/* Enable NKRO indicator LED on FN press */
#define NKRO_LED_INDEX 85

/* Enable FN indicator LED on FN press */
#define FN_LED_INDEX 101

/* Enable RGB mode on/off indicator LED on FN press */
#define RGB_MODE_LED_INDEX 15

/* Enable selected RGB mode indicator LEDs on FN press */
#define SELECTED_RGB_MODE_LED

/* Enable MAC mode on/off indicator LED on FN press */
#define MAC_LED_INDEX 86

// Manage indicators LEDs pre-processor directives
#if defined(CAPS_LOCK_LED_INDEX) || \
    defined(NUM_LOCK_LED_INDEX) ||  \
    defined(SCROLL_LOCK_LED_INDEX)
#    define HOST_INDICATOR_KEYS
#endif

#if defined(NKRO_LED_INDEX) ||          \
    defined(FN_LED_INDEX) ||            \
    defined(RGB_MODE_LED_INDEX) ||      \
    defined(SELECTED_RGB_MODE_LED) ||   \
    defined(MAC_LED_INDEX)
#    define FN_INDICATOR_KEYS
#endif

#if defined(RGB_MATRIX_ENABLE) && ( \
    defined(HOST_INDICATOR_KEYS) || \
    defined(FN_INDICATOR_KEYS))
#    define STATUS_INDICATOR_KEYS
#endif
