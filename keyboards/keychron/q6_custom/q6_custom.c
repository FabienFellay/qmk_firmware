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

#include "quantum.h"

const matrix_row_t matrix_mask[] = {
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111111111,
    0b11111111111111101111,
};

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif // DIP_SWITCH_ENABLE

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || \
    defined(NUM_LOCK_LED_INDEX) || defined(SCROLL_LOCK_LED_INDEX))
#    define HOST_STATUS_KEYS
#endif

#ifdef HOST_STATUS_KEYS

static const RGB rgb_on = (RGB){RGB_WHITE};
static const RGB rgb_off = (RGB){RGB_OFF};

typedef union {
  uint32_t raw;
  struct {
    bool    rgb_matrix_effect_enable : 1;
  };
} kb_config_t;

kb_config_t kb_config;

// Keyboard level default EEPROM settings after EEPROM reset
void eeconfig_init_kb(void) {
    kb_config.raw = 0;
    kb_config.rgb_matrix_effect_enable = false;  // We want the rgb effect disabled by default
    eeconfig_update_kb(kb_config.raw);  // Write default value to EEPROM

    eeconfig_init_user();
}

// Keyboard level matrix init
void keyboard_post_init_kb(void) {
    // Read the custom keyboard config from EEPROM
    kb_config.raw = eeconfig_read_kb();

    // Set initial rgb effect state after boot
    if (!kb_config.rgb_matrix_effect_enable) {
        // Disable the rgb effect by setting the mode and the color without writing to the EEPROM
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 0);
    }
    // else the whole rgb config is automatically loaded from EEPROM
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                // On key press
                if (!rgb_matrix_is_enabled() || (rgb_matrix_get_flags() != LED_FLAG_ALL)) {
                    // Ensure that the rgb matrix feature is enabled with all flags
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable();
                }

                // Toggle rgb matrix effect
                if (kb_config.rgb_matrix_effect_enable) {
                    // Disable the rgb effect by setting the mode and the color without writing to the EEPROM
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv_noeeprom(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 0);
                    kb_config.rgb_matrix_effect_enable = false;
                    eeconfig_update_kb(kb_config.raw); // write the custom keyboard settings to EEPROM

                } else {
                    // Get the mode and the color back from EEPROM
                    rgb_matrix_reload_from_eeprom();
                    kb_config.rgb_matrix_effect_enable = true;
                    eeconfig_update_kb(kb_config.raw); // write the custom keyboard settings to EEPROM
                }
            }
            return false;  // Skip all further processing of this key

        // Disable the RGB matrix management if the rgb matrix effect is off
        case RGB_MODE_FORWARD ... RGB_MODE_TWINKLE:  // For any of the RGB codes (see quantum/keycodes.h for reference)
            // Continue further processing of those keys only if the rgb matrix effect is on
            return kb_config.rgb_matrix_effect_enable;

        default:
            return true;  // Process all other keycodes normally
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    // RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);
#    if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, rgb_on.r, rgb_on.g, rgb_on.b);
    } else {
        if (!kb_config.rgb_matrix_effect_enable) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, rgb_off.r, rgb_off.g, rgb_off.b);
        }
    }
#    endif // CAPS_LOCK_LED_INDEX
#    if defined(NUM_LOCK_LED_INDEX)
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, rgb_on.r, rgb_on.g, rgb_on.b);
    } else {
        if (!kb_config.rgb_matrix_effect_enable) {
            RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, rgb_off.r, rgb_off.g, rgb_off.b);
        }
    }
#    endif // NUM_LOCK_LED_INDEX
#    if defined(SCROLL_LOCK_LED_INDEX)
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(SCROLL_LOCK_LED_INDEX, rgb_on.r, rgb_on.g, rgb_on.b);
    } else {
        if (!kb_config.rgb_matrix_effect_enable) {
            RGB_MATRIX_INDICATOR_SET_COLOR(SCROLL_LOCK_LED_INDEX, rgb_off.r, rgb_off.g, rgb_off.b);
        }
    }
#    endif // SCROLL_LOCK_LED_INDEX
    return true;
}

#endif // HOST_STATUS_KEYS
