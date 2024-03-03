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

/* Default EEPROM settings after EEPROM reset: change the rgb matrix default */

// Possible values for 17 increments step in saturated range 0-255 (16 repeatable levels)
// 0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255
//
// Possible values for 15 increments step in saturated range 0-255 (18 repeatable levels)
// 0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255

/* Select the default RGB matrix effect */
#ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif  // ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE

/* Select the default RGB matrix color (not exactly pure hsv green) */
#define RGB_MATRIX_HUE_STEP 8       // Refined alternative: 4
#define RGB_MATRIX_DEFAULT_HUE 80   // Reachable initial hue level, close to pure green
// Hue cyclic range: this color ensures passing by pure hsv red considering the chosen hue step
// We can only pass to a single pure color among the 6 pure hues r-g-b-c-m-y (pure red is chosen as the reference)

#define RGB_MATRIX_SAT_STEP 15      // 18 repeatable levels
#define RGB_MATRIX_DEFAULT_SAT 255  // Reachable initial saturation level

#define RGB_MATRIX_VAL_STEP 15      // 18 repeatable levels
#define RGB_MATRIX_DEFAULT_VAL 255  // Reachable initial value level

/* Select the default RGB matrix effect speed (value from 0 to 255) */
#define RGB_MATRIX_SPD_STEP 15      // 18 repeatable levels
#define RGB_MATRIX_DEFAULT_SPD 75   // Reachable initial value level

/* Select the default RGB matrix status after EEPROM reset */
#ifdef STATUS_INDICATOR_KEYS
// Enable RGB feature by default to allow indicator LEDs
#    define RGB_MATRIX_DEFAULT_ON true
// Disable RGB effect by default just after an EEPROM reset
#    define RGB_MATRIX_EFFECT_DEFAULT_ON false
#else
// Disable RGB effect by default just after an EEPROM reset
#    define RGB_MATRIX_DEFAULT_ON false
#endif  // STATUS_INDICATOR_KEYS

/* Select the default RGB matrix flag */
// Setting this from config.h is not implemented yet: all flags enabled by default

/* Select the default NKRO status after EEPROM reset */
#define NKRO_DEFAULT_ON true

/* Select the default debug message status after EEPROM reset */
#define DEBUG_MESSAGE_DEFAULT_ON false

/* Tap count needed for toggling a feature (like changing layer with TT) */
#define TAPPING_TOGGLE 2

/* Period of tapping (ms) */
#define TAPPING_TERM 100

/* Make tap and hold keys work better for fast typists */
#define HOLD_ON_OTHER_KEY_PRESS
// Immediately decide on hold instead of tap (without waiting the tapping term) if another key is pressed
