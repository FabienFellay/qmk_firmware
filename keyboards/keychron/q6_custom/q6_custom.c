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

#include "q6_custom.h"

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? WIN_BASE : MAC_BASE));
    }
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    // Clear any FN layer on default layer change
    layer_clear();

    return default_layer_state_set_user(state);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    // Avoid to enable the wrong FN layer when the FN key and the DIP switch are pushed at the same time
    state &= (default_layer_state << 1);

    return layer_state_set_user(state);
}

#endif  // DIP_SWITCH_ENABLE

// Custom EEPROM structure
kb_config_t kb_config;

// Keyboard level default EEPROM settings after EEPROM reset
void eeconfig_init_kb(void) {
    kb_config.raw = 0;

    kb_config.debug_message_enable = DEBUG_MESSAGE_DEFAULT_ON;

#ifdef STATUS_INDICATOR_KEYS
    kb_config.rgb_matrix_effect_enable = RGB_MATRIX_EFFECT_DEFAULT_ON;
    kb_config.mode = RGB_MATRIX_DEFAULT_MODE;
    kb_config.value = RGB_MATRIX_DEFAULT_VAL;
#endif  // STATUS_INDICATOR_KEYS

    eeconfig_update_kb(kb_config.raw);  // Write default value to EEPROM

    eeconfig_init_user();
}

// Keyboard level matrix init
void keyboard_post_init_kb(void) {
    // Read the custom keyboard config from EEPROM
    kb_config.raw = eeconfig_read_kb();

#ifdef STATUS_INDICATOR_KEYS
    // Set initial rgb effect state after boot
    if (!kb_config.rgb_matrix_effect_enable) {
        // Disable the rgb effect by setting the mode and the color without writing to the EEPROM
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, 0);
    }  // else: the whole rgb config is automatically loaded from EEPROM
#endif  // STATUS_INDICATOR_KEYS

    // Debug configuration
#ifndef NO_DEBUG
    debug_enable = kb_config.debug_message_enable;
#else
    debug_enable = false;
#endif  // NO_DEBUG
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;
}

// Indicators LEDs controls and debug state management
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
#ifdef STATUS_INDICATOR_KEYS
        case RGB_TOG:
            if (record->event.pressed) {
                // On key press
                if (!rgb_matrix_is_enabled() || (rgb_matrix_get_flags() != LED_FLAG_ALL)) {
                    // Ensure that the rgb matrix feature is enabled with all flags
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable();
                    eeconfig_update_rgb_matrix();  // Force writing the updated rgb EEPROM now (flush)
                }

                // Toggle rgb matrix effect
                kb_config.rgb_matrix_effect_enable ^= 1;
                if (kb_config.rgb_matrix_effect_enable) {
                    // Change rgb matrix effect
                    eeconfig_update_kb(kb_config.raw);  // Write the custom keyboard settings to EEPROM

                    // Enable the rgb effect by getting the mode and the color hsv value back from the custom keyboard settings
                    rgb_matrix_mode(kb_config.mode);
                    rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), kb_config.value);

                } else {
                    // Store the mode and the color hsv value in the custom keyboard settings
                    kb_config.mode = rgb_matrix_get_mode();
                    kb_config.value = rgb_matrix_get_val();
                    eeconfig_update_kb(kb_config.raw);  // Write the custom keyboard settings to EEPROM

                    // Disable the rgb effect by setting the mode and the color hsv value without writing to the EEPROM
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                    rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 0);
                }
            }
            return false;  // Skip all further processing of this key

        // Disable the RGB matrix management if the rgb matrix effect is off
        case RGB_MODE_FORWARD ... RGB_MODE_TWINKLE:  // For any of the RGB codes (see quantum/keycodes.h for reference)
            // Continue further processing of those keys only if the rgb matrix effect is on
            return kb_config.rgb_matrix_effect_enable;
#endif  // STATUS_INDICATOR_KEYS

#ifndef NO_DEBUG
        // Manage EEPROM config for debug state
        case DB_TOGG:
            if (record->event.pressed) {
                // On key press
                debug_enable ^= 1;
                if (debug_enable) {
                    print("DEBUG: enabled.\n");
                } else {
                    print("DEBUG: disabled.\n");
                }

                // Write the custom keyboard settings to EEPROM
                kb_config.debug_message_enable = debug_enable;
                eeconfig_update_kb(kb_config.raw);
            }
            return false;  // Skip all further processing of this key
#endif  // NO_DEBUG

        default:
            return true;  // Process all other keycodes normally
    }
}

#ifdef STATUS_INDICATOR_KEYS

// Indicators LEDs helper function-like macro
#    define RGB_MATRIX_INDICATOR_SWITCH_KEY(condition, index)                   \
    if (condition) {                                                            \
        RGB_MATRIX_INDICATOR_SET_COLOR(index, rgb_on.r, rgb_on.g, rgb_on.b);    \
    } else if (                                                                 \
        !(kb_config.rgb_matrix_effect_enable &&                                 \
        HAS_ANY_FLAGS(g_led_config.flags[index], rgb_matrix_get_flags()))) {    \
        RGB_MATRIX_INDICATOR_SET_COLOR(index, rgb_off.r, rgb_off.g, rgb_off.b); \
    }  // else: the selected effect will repaint the key

// Selected mode indicators LEDs
#    ifdef SELECTED_RGB_MODE_LED

// Units and tens index ranges
#        define NUM_BASE 10

static const uint8_t mode_units_index_range[NUM_BASE] = {
    106, 92, 93, 94, 74, 75, 76, 57, 58, 59  // Units on the numeric keypad
};
static const uint8_t mode_tens_index_range[NUM_BASE] = {
    30, 21, 22, 23, 24, 25, 26, 27, 28, 29  // Tens on the main numeric row
};

// Selected mode indicators LEDs helper function-like macro
#        define RGB_MATRIX_INDICATOR_SELECTED_MODE(mode, condition, units_index, tens_index)    \
    /* Get units and tens from the mode (valid for mode < 100 and then wrap back to 0) */       \
    const uint8_t units = mode % NUM_BASE;                                                      \
    const uint8_t tens = (mode / NUM_BASE) % NUM_BASE;                                          \
    /* Units range scanning */                                                                  \
    for (uint8_t i = 0; i < NUM_BASE; ++i) {                                                    \
        RGB_MATRIX_INDICATOR_SWITCH_KEY((i == units) && condition, units_index[i]);             \
    }                                                                                           \
    /* Tens range scanning */                                                                   \
    for (uint8_t i = 0; i < NUM_BASE; ++i) {                                                    \
        RGB_MATRIX_INDICATOR_SWITCH_KEY((i == tens) && condition, tens_index[i]);               \
    }

#    endif  // SELECTED_RGB_MODE_LED

// Process indicators LEDs
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    // Prevent VIA from bypassing the mode and the color hsv value when the rgb effect is disabled
    if (!kb_config.rgb_matrix_effect_enable) {
        if (rgb_matrix_get_mode() != RGB_MATRIX_SOLID_COLOR) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        }

        if (rgb_matrix_get_val() != 0) {
            rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), 0);
        }
        // Avoid writing anything to the EEPROM here (function called at high frequency, potential risk of writing too often)
    }

#    ifdef CAPS_LOCK_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(host_keyboard_led_state().caps_lock, CAPS_LOCK_LED_INDEX);
#    endif  // CAPS_LOCK_LED_INDEX

#    ifdef NUM_LOCK_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(host_keyboard_led_state().num_lock, NUM_LOCK_LED_INDEX);
#    endif  // NUM_LOCK_LED_INDEX

#    ifdef SCROLL_LOCK_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(host_keyboard_led_state().scroll_lock, SCROLL_LOCK_LED_INDEX);
#    endif  // SCROLL_LOCK_LED_INDEX

#    ifdef FN_INDICATOR_KEYS

    const bool fn_layer_on = (IS_LAYER_ON(MAC_FN) || IS_LAYER_ON(WIN_FN));

#        ifdef FN_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(fn_layer_on, FN_LED_INDEX);
#        endif  // FN_LED_INDEX

#        ifdef NKRO_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(fn_layer_on && keymap_config.nkro, NKRO_LED_INDEX);
#        endif  // NKRO_LED_INDEX

#        ifdef RGB_MODE_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(fn_layer_on && kb_config.rgb_matrix_effect_enable, RGB_MODE_LED_INDEX);
#        endif  // RGB_MODE_LED_INDEX

#        ifdef SELECTED_RGB_MODE_LED
    RGB_MATRIX_INDICATOR_SELECTED_MODE(
        rgb_matrix_config.mode,
        fn_layer_on && kb_config.rgb_matrix_effect_enable,
        mode_units_index_range,
        mode_tens_index_range);
#        endif  // SELECTED_RGB_MODE_LED

#        ifdef MAC_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(fn_layer_on && (default_layer_state == (1UL << MAC_BASE)), MAC_LED_INDEX);
#        endif  // MAC_LED_INDEX

#        ifdef DB_LED_INDEX
    RGB_MATRIX_INDICATOR_SWITCH_KEY(fn_layer_on && debug_config.enable, DB_LED_INDEX);
#        endif  // DB_LED_INDEX

#    endif  // FN_INDICATOR_KEYS

    return true;
}

#endif  // STATUS_INDICATOR_KEYS
