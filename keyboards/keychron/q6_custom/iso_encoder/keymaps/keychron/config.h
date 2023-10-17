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

/* Select the default RGB matrix status (enable RGB feature by default) */
// Setting this from config.h is not implemented: enabled by default

/* Select the default RGB matrix effect */
#ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif

/* Select the default RGB matrix color (not exactly pure hsv green) */
#define RGB_MATRIX_HUE_STEP 8
// This color ensures passing by pure hsv red considering the chosen hue step
#define RGB_MATRIX_DEFAULT_HUE 80  // Close to green
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 255

/* Select the default RGB matrix effect speed (value from 0 to 255) */
#define RGB_MATRIX_DEFAULT_SPD UINT8_MAX / 4

/* Select the default RGB matrix flag (disable RGB effect on all keys by default) */
// Setting this from config.h is not implemented: all flags enabled by default
