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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "q6_custom.h"

// Constants, declarations and definitions for the LEDs notification
#define BLINK_WAIT_MS 300
#define PRE_WAIT_MS 600
#define POST_WAIT_MS 600
#define COL_SEQ_LEN 3

// LEDs notification color sequences
static const RGB rgb_col_seq[COL_SEQ_LEN] = {(RGB){RGB_RED},  (RGB){RGB_GREEN},   (RGB){RGB_BLUE}};
static const RGB cmy_col_seq[COL_SEQ_LEN] = {(RGB){RGB_CYAN}, (RGB){RGB_MAGENTA}, (RGB){RGB_YELLOW}};

extern void rgb_matrix_update_pwm_buffers(void);

// Soft reboot and EEPROM reset LEDs notification
void led_notification(const RGB col_seq[]) {
    if (!rgb_matrix_is_enabled()) {
        // Ensure that the rgb matrix feature is enabled
        rgb_matrix_enable_noeeprom();
    }

    rgb_matrix_set_color_all(RGB_OFF);  // Set a single color to the whole LED matrix
    rgb_matrix_update_pwm_buffers();  // Force LED driver to process the last requests
    wait_ms(PRE_WAIT_MS);  // Blocking call

    // LED blinking (it cycles through various colors)
    for (uint8_t i = 0; i < COL_SEQ_LEN; i++) {
        rgb_matrix_set_color_all(col_seq[i].r, col_seq[i].g, col_seq[i].b);
        rgb_matrix_update_pwm_buffers();
        wait_ms(BLINK_WAIT_MS);

        rgb_matrix_set_color_all(RGB_OFF);
        rgb_matrix_update_pwm_buffers();
        wait_ms(BLINK_WAIT_MS);
    }

    rgb_matrix_set_color_all(RGB_OFF);
    rgb_matrix_update_pwm_buffers();
    wait_ms(POST_WAIT_MS);
}

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    KC_MUTE,    KC_SNAP,  KC_SIRI,  RGB_MOD,  KC_F13,   KC_F14,   KC_F15,   KC_F16,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,                                   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,              KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD, KC_ROPTN, MO(MAC_FN), KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT,  KC_PENT),
    [MAC_FN] = LAYOUT_iso_110(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     RGB_TOG,    _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    QK_RBT,     _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                EE_CLR,   _______,  _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                                  KC_MS_L,  KC_BTN3,  KC_MS_R,  KC_BTN8,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,              KC_WH_U,            KC_BTN4,  KC_MS_D,  KC_BTN5,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    KC_WH_L,  KC_WH_D,  KC_WH_R,  KC_BTN6,            KC_BTN7,  _______),
    [WIN_BASE] = LAYOUT_iso_110(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,     KC_MUTE,    KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_WSCH,  KC_MAIL,  KC_CALC,  KC_MYCM,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,     KC_BSPC,    KC_INS,   KC_HOME,  KC_PGUP,  KC_NUM,   KC_PSLS,  KC_PAST,  KC_PMNS,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                KC_DEL,   KC_END,   KC_PGDN,  KC_P7,    KC_P8,    KC_P9,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,                                   KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,              KC_UP,              KC_P1,    KC_P2,    KC_P3,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_RWIN,  MO(WIN_FN), KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,              KC_PDOT,  KC_PENT),
    [WIN_FN] = LAYOUT_iso_110(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,    RGB_TOG,    _______,  _______,  RGB_TOG,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    QK_RBT,     _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                EE_CLR,   _______,  _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,                                  KC_MS_L,  KC_BTN3,  KC_MS_R,  KC_BTN8,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,              KC_WH_U,            KC_BTN4,  KC_MS_D,  KC_BTN5,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,    KC_WH_L,  KC_WH_D,  KC_WH_R,  KC_BTN6,            KC_BTN7,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI) }
};
#endif

// clang-format on

void housekeeping_task_user(void) {
    housekeeping_task_keychron();
}

// Protect soft reboot and EEPROM reset features with timers and add LED notification
#define RESET_HOLD_TIME_MS 4000

static bool reboot_key_hold = false;
static uint16_t reboot_key_timer = 0;

static bool reset_key_hold = false;
static uint16_t reset_key_timer = 0;

// Manage soft reboot and EEPROM reset timers
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(!process_record_keychron(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case QK_RBT:
            if (record->event.pressed) {
                // On key press
                reboot_key_hold = true;
                reboot_key_timer = record->event.time;  // Set the reboot key timer
            } else {
                // On key release
                reboot_key_hold = false;
                reboot_key_timer = 0;  // Reset the reboot key timer
            }
            return false;  // Skip all further processing of this key
        case EE_CLR:
            if (record->event.pressed) {
                // On key press
                reset_key_hold = true;
                reset_key_timer = record->event.time;  // Set the reset key timer
            } else {
                // On key release
                reset_key_hold = false;
                reset_key_timer = 0;  // Reset the reset key timer
            }
            return false;  // Skip all further processing of this key
        default:
            return true;  // Process all other keycodes normally
    }
}

// Take care: this is called at every matrix scan (highest possible frequency)
void matrix_scan_user(void) {
    if (reboot_key_hold == true) {
        if (timer_elapsed(reboot_key_timer) > RESET_HOLD_TIME_MS) {  // ms
            reboot_key_hold = false;
            reboot_key_timer = 0;  // Reset the reboot key timer

            // LEDs notification before reboot (blocking call)
            led_notification(rgb_col_seq);

            soft_reset_keyboard();  // Soft reboot
            return;
        }
    }
    if (reset_key_hold == true) {
        if (timer_elapsed(reset_key_timer) > RESET_HOLD_TIME_MS) {  // ms
            reset_key_hold = false;
            reset_key_timer = 0;  // Reset the reset key timer

            // LEDs notification before EEPROM reset (blocking call)
            led_notification(cmy_col_seq);

            eeconfig_disable();  // Reset EEPROM to default
            soft_reset_keyboard();  // Soft reboot
            return;
        }
    }
}

// Keymap level default EEPROM settings after EEPROM reset: N-key rollover
void eeconfig_init_user(void) {
    // Enable NKRO immediately after reset
    keymap_config.raw = 0;  // All options disabled

    clear_keyboard();  // Clear first buffer to prevent stuck keys
    keymap_config.nkro = true;  // Enable NKRO
    eeconfig_update_keymap(keymap_config.raw);  // Write default value to EEPROM now
    clear_keyboard();  // Clear to prevent stuck keys
}
