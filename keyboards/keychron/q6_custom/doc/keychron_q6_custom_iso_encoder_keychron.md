\newpage

# Flashing the firmware

This firmware is based on [QMK Firmware](https://docs.qmk.fm/#/) (Quantum Mechanical Keyboard), an [open source project](https://github.com/qmk/qmk_firmware) and community centered around developing firmwares for computer input devices such as keyboards, mice, and MIDI devices. The open source nature of QMK allows users with enough skills or developers to build their own QMK firmware for a custom keyboard to control backlight effects, indicators, macros, custom keycodes, and mouse commands on different keymap layers. Directly modifying the source code of the firmware is what offers the highest possible level of customization.

## Flashing a keyboard previously running the factory firmware

**\textwarn{\faWarning{} Warning}:** This keyboard firmware has been designed for the [Keychron Q6 Knob Version with ISO layout](https://www.keychron.com/products/keychron-q6-qmk-custom-mechanical-keyboard-iso-layout-collection). If your [Keychron Q6](https://www.keychron.com/products/keychron-q6-qmk-custom-mechanical-keyboard) keyboard does not have a knob and/or it has an **ANSI layout**, do not flash this firmware.

When flashing this firmware for the first time, the keyboard still has the factory firmware running. In that case, the flashing procedure is less straightforward as you need to remove the space bar keycap to access the reset button. This button is used to load the bootloader and put the keyboard into DFU mode (Device Firmware Upgrade, a mechanism for upgrading the firmware of USB devices). The following is based on the procedure from the [Keychron website](https://www.keychron.com/pages/keychron-q6-user-guide):

1. Plug in the USB cable and clear the keyboard's EEPROM by pressing on `Fn` + `J` + `Z` together during 4 seconds. All key LEDs will shortly flash in red. By clearing the EEPROM, the RGB matrix lighting setting and any keymap customization done with the VIA configurator will be reset to their defaults. Clearing the EEPROM before flashing a new firmware might be necessary if the used EEPROM structure differs between them.<br>
**Note:** The key combination `Fn` + `J` + `Z` applies to the reference US layout (QWERTY) and you have to adapt it depending on the keycap layout you are using. For example, the key combination is `Fn` + `J` + `Y` if you have a Swiss layout keycaps set (QWERTZ).

2. Download the firmware **keychron_q6_custom_iso_encoder_keychron.bin** from [GitHub: FabienFellay](https://github.com/FabienFellay/qmk_firmware/releases) and download **QMK Toolbox** from [GitHub: QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) before installing it.

3. Unplug the USB cable from the keyboard and open the locally installed **QMK Toolbox** application.

4. Remove the space bar keycap to access the reset button on the left side of the space bar switch on the PCB.

5. Press down and hold the reset button before plugging in the USB cable again. The keyboard will now enter into DFU mode and **QMK Toolbox** will display `STM32 DFU device connected ...` in yellow. The DFU mode is a special mode of the keyboard where its functionality are momentarily disabled (the keys are unresponsive): it only waits for a firmware to be flashed.

6. Click on the **Open** button, select the previously downloaded **.bin** firmware and click on the **Flash** button. It will now start flashing.<br>
**\textwarn{\faWarning{} Warning}:** Do not unplug the USB cable during flash.

7. Wait a few seconds until the message `STM32 DFU device disconnected ...` appears in yellow in **QMK Toolbox**. Now, the keyboard will reboot using the new firmware.

\newpage

## Flashing a keyboard previously running this new custom firmware

Once the new firmware has been applied, the procedure to flash another one is now different than the factory firmware. Notably, the combination `Fn` + `J` + `Z` for clearing the EEPROM before an upgrade will not work anymore. Instead, one has now to unplug the USB cable from the keyboard, press down and hold the `Esc` key before plugging in the USB cable again. Still hold the `Esc` key until DFU mode is confirmed in yellow in **QMK Toolbox**. This new mechanism (known as the Bootmagic feature of [QMK Firmware](https://github.com/qmk/qmk_firmware)) also automatically clears the EEPROM for you before flashing.

If you have to frequently flash various firmwares (for example, because you are developing one and you want to frequently test your code), unplugging and plugging in the USB cable in order to reboot the keyboard can become cumbersome. The new firmware you just flashed now provides a mechanism to reboot the keyboard without unplugging the cable: just press on `Fn` + `Backspace` together during 4 seconds (actually `Fn` must be pressed slightly before `Backspace` in order to properly change the layer, see the [layers description](#keymaps) later). All key LEDs will now shortly flash 3 times in red, green, and blue (in this order) indicating that the keyboard is rebooting.

Therefore, the easiest way to enter into DFU mode now is to combine this with the `Esc` key: during the red-green-blue flash, quickly press and hold the `Esc` key. `Fn` and `Backspace` can now be released but maintain the `Esc` key for a few more seconds until DFU mode is confirmed in yellow in **QMK Toolbox**. The rest of the procedure remains unchanged, just select the firmware of your choice using **QMK Toolbox**.

Moreover, on the new firmware, if you want an equivalent of the old combination `Fn` + `J` + `Z` for just clearing the EEPROM, now press on `Fn` + `Delete` together during 4 seconds. All key LEDs will now shortly flash 3 times in cyan, magenta, and yellow (in this order) indicating that the keyboard memory is being reset to its default. This may be useful if you lose track of what you did with the RGB matrix lighting setting or with the VIA configurator customization and you want to quickly go back to a known default state.

Finally, if you want to flash back the factory firmware, you can get it from the [Keychron website](https://www.keychron.com/pages/firmware-and-json-files-of-the-keychron-qmk-keyboards) and follow the above-mentioned instructions to flash. For flashing the officially provided firmware, note that Keychron moved now to their [own solution](https://www.keychron.com/pages/how-to-factory-reset-or-use-the-launcher-web-app-to-flash-firmware-for-your-keyboard) called [Launcher](https://www.keychron.com/blogs/news/how-to-use-launcher-to-program-your-keyboard).

\newpage

# RGB matrix lighting

Each key of the keyboard is equipped with a full RGB LED allowing 16'777'216 colors. As each key can be illuminated independently, we refer to it as a matrix of RGB LEDs. This matrix can be used for various indicators of the keyboard and OS states as well as decorative lighting effect.

**Note:** We remind that the key combinations involving `Fn` + `key` applies to the reference US layout (QWERTY) and you have to adapt it depending on the keycap layout you are using or see the [layers description](#keymaps) to remove any ambiguity.

## Lighting effects

The lighting effects can be enabled or disabled by pressing on `Fn` + `Tab` or `Fn` + `Knob Press` or `Fn` + \texttt{\faLightbulbO{}} (the key labeled as `015` on the [LEDs indexes keymap](#leds-indexes)). Once the lighting effects are enabled, you can select the one you want by pressing on `Fn` + `Q` to switch to the next effect in the list. Use `Fn` + `A` to switch to the previous effect. In addition, the list can be explored circularly. There are 20 available effects shown below:

| Effect number | Effect name | Effect type |
| ------------: | ----------- | ----------- |
| 01. | `solid_color` | Monochromatic |
| 02. | `breathing` | Monochromatic |
| 03. | `band_spiral_val` | Monochromatic |
| 04. | `cycle_all` | Rainbow |
| 05. | `cycle_left_right` | Rainbow |
| 06. | `cycle_up_down` | Rainbow |
| 07. | `rainbow_moving_chevron` | Rainbow |
| 08. | `cycle_out_in` | Rainbow |
| 09. | `cycle_out_in_dual` | Rainbow |
| 10. | `cycle_pinwheel` | Rainbow |
| 11. | `cycle_spiral` | Rainbow |
| 12. | `dual_beacon` | Rainbow |
| 13. | `rainbow_beacon` | Rainbow |
| 14. | `typing_heatmap` | Reactive + Rainbow |
| 15. | `solid_reactive_simple` | Reactive + Monochromatic |
| 16. | `solid_reactive_multiwide` | Reactive + Monochromatic |
| 17. | `solid_reactive_multinexus` | Reactive + Monochromatic |
| 18. | `multisplash` | Reactive + Rainbow |
| 19. | `solid_multisplash` | Reactive + Monochromatic |
| 20. | `riverflow` | Monochromatic |

After an EEPROM reset, the default effect is always set to the effect number 15 `solid_reactive_simple` and the lighting is disabled. However, the last effect selected as well as the lighting toggle state will be then stored in the keyboard memory and survives keyboard reboots. You can increase and decrease the effect brightness (referred to as the value) by using `Fn` + `W` and `Fn` + `S` respectively. Some effects are monochromatic and others involves cycling through the hue circle (the so-called rainbow effects). For all the monochromatic effects, you can select the hue by using `Fn` + `E` and `Fn` + `D` to move forward and backward in the hue circle. Alternatively, the hue can be adjusted by using `Fn` + `Knob Turn`. For all effects, you can increase (vivid colors) and decrease (greyish colors) the saturation by using `Fn` + `R` and `Fn` + `F`. Finally, some effects shows various dynamic patterns. The evolution speed of those patterns can be adjusted by using `Fn` + `T` (increase) and `Fn` + `G` (decrease). A zero speed will freeze the animations.

Adjusting the hue, saturation, and value (HSV) allows to freely select a color for the monochromatic effects, covering the full RGB LEDs color space. The rainbow effects only honors the specified saturation and value (brightness) of the chosen color, as the hue will be dynamic. Keep in mind that black corresponds to no lighting at all and is only obtained when brightness is zero. All effects will not be visible in that case, even if they are enabled. The color and speed are also stored in the keyboard memory. The default color after an EEPROM reset is a bright green.

\newpage

## Indicators

On top of the lighting effects, the LEDs matrix is also used for various indicators, always lighted in bright white. The limitation of this technique is that the indicators may become indistinguishable from an effect background if white is chosen as the effect color. Refer to the [LEDs flags](#leds-flags) to have a summary of all the keys used as indicators.

### Host indicators

The host indicators are always active (whether the RGB lighting effects are enabled or not) and are there to reflect a state of the computer OS linked to the keyboard. These are typically `Num Lock` and `Caps Lock`. On Windows (and possibly on Linux), the `Scroll Lock` is available in addition when the Windows/Linux layers 2 and 3 are used (see the [layers description](#keymaps)). Contrary to what we may think, those indicators are not keyboard states (the information is sent to the keyboard by the OS). Some keyboards have dedicated LEDs (not linked to a key) to display the host indicators. This is not the case with the **Keychron Q6** keyboard.

### Keyboard indicators

The keyboard indicators are also always active (whether the RGB lighting effects are enabled or not) and are there to reflect a state of the keyboard internal machinery. The computer OS linked to the keyboard knows nothing about them. All the keyboard indicators described below are only shown when the secondary layer is active (i.e. when the `Fn` key is pressed). This design choice has been made in order to avoid having too many indicators lighted up permanently. The keyboard indicators includes the following:

* Each time that the `Fn` key itself is pressed (or quickly double tapped if you want a permanent hold), this key is lighted up in bright white. It indicates that the secondary layer (also called the FN layer) is active. To go back to the base layer, release the `Fn` key (or quickly double tapped again if the FN layer was in permanent hold). When the `Fn` is not lighted up, you are in the base layer.

* When NKRO (N-key rollover) is enabled, the `N` key is lighted up. You can toggle NKRO on or off by pressing on `Fn` + `N`. NKRO is the keyboard ability to correctly detect each keypress regardless of how many other keys are being pressed or held down at the time and then to report them without miss to the computer OS. When NKRO is disabled, the keyboard is limited to the standard USB 6-key rollover (6KRO).

* When the debug mode is enabled, the `B` key is lighted up (see the [debug mode description](#debug-mode)). You can toggle the debug mode on or off by pressing on `Fn` + `B`.

* When the keyboard is in Mac mode (layer 0 and 1), the `M` key is lighted up. If not, it means that you are in Windows/Linux mode (layers 2 and 3). You cannot toggle the Mac mode by pressing on `Fn` + `M`. Use the DIP switch at the top left of the keyboard instead.

* When the lighting effects are enabled, the \texttt{\faLightbulbO{}} key (`Pause/Break` in Windows mode, `RGB Mode+` in Mac mode) is lighted up. On top of that, one can directly know the chosen [lighting effect number](#lighting-effects) by reading it on the numeric keys: the tens digit is shown on the main typing pad numeric keys while the units digit appears on the keypad numeric keys. This trick allows to keep track of the chosen lighting effect, especially for effects that are only visible when keys are pressed (the so-called reactive effects).

\newpage

# Keymaps

## The 4 layers

One of the key feature of the [QMK Firmware](https://github.com/qmk/qmk_firmware) run by this keyboard is the ability to use layers. In our case, this will just amounts to a function key (referred to as the `Fn` key) that allows for alternate actions associated with the keys, much like what you would see on a laptop or a tablet keyboard.

There are 4 layers on this keyboard: the layer 0 and 1 are reserved for the Mac mode and the layer 2 and 3 for the Windows/Linux mode. The even-numbered layers 0 and 2 are called the **base** layers of each mode. These layers holds the standard functions of the keys, used most of the time (i.e. normal operations of the keyboard). On the other hand, the odd-numbered layers 1 and 3 are called the **FN** layers of each mode. They mostly serves to control additional features, summarized as follows:

* Toggle between the function keys (F1-F16) and the media keys. The exact behavior depends on the selected mode: with Windows/Linux mode, the function keys are on the base layer and the media keys are accessed on the FN layer. With Mac mode, the opposite is true.
* Control the RGB effects and its various settings.
* Toggle special features such as NKRO and debug mode.
* Use the keyboard as a mouse (mouse buttons, pointer, and wheel control).
* Reboot the keyboard or reset its memory. In order to prevent reboot and reset from being triggered inadvertently, those features are protected by timers that require 4 seconds press and hold before taking effect.

Note that only a subset of the keys have a special purpose on the FN layer. The others keys keep their normal behavior, even when the FN layer is active (we call them the **transparent** keys of the FN layer, see the [keycode description](#qmk-keymaps) on the next pages).

To switch between Mac mode and Windows/Linux mode, use the DIP (dual in-line package) switch located at the top left of the keyboard. When the switch is pushed to the left, the keyboard jumps to the layer 0 (Mac base). Push the switch to the right and the keyboard jumps to the layer 2 (Windows base).

Pressing and holding the `Fn` key when the keyboard is in the layer 0 (Mac base) will jump to the layer 1 (Mac FN). Similarly, pressing and holding the `Fn` key when the keyboard is in the layer 2 (Windows base) will jump to the layer 3 (Windows FN). Note that the effect of the `Fn` key press is momentary and lasts only as long as it is hold.

On top of that, having to hold the `Fn` key to stay on the FN layers can become cumbersome in some situations (for example when using the mouse control). Therefore, one can permanently enable the FN layers by quickly double tapping the `Fn` key (permanent hold). To toggle back the base layers from a permanent FN hold, one has to quickly double tap the `Fn` key again. Note that, during a permanent FN hold, the momentary effect of a single `Fn` key press and hold is inverted: it will momentarily go back to the base layers. In case of doubt, one can immediately knows the FN hold state at any time by looking at the `Fn` key indicator: it is always lighted up in bright white when the FN layers are active.

\newpage

## QMK keymaps

This keyboard features a large ISO layout with 109 keys (including a numeric keypad) and a knob (thus the name ISO-110). Keyboards of this size are referred to as keyboard with 100% layout.

The 4 layers keymaps are presented on the next pages with each key associated with a [QMK keycode](https://docs.qmk.fm/keycodes). The used keycode labels are derived from the QMK keycodes **defines** but we omitted the `KC_` prefix (KC meaning Key Code) before most of the keycodes, all underlines were replaced by spaces and `KC_TRNS` (transparent keys) was replaced by `____`. Refer to the [QMK full list](https://docs.qmk.fm/keycodes) for a comprehensive overview. The subset of the used keycode can be found below. Note that some of the keycodes are not in the [QMK full list](https://docs.qmk.fm/keycodes) because they are special custom action keys only defined for this firmware.

### Base layers keys

| Keycode label | Description |
| ---- | ---------------- |
| `ESC` | Escape |
| `GRV` | \texttt{\fixedtextasciigrave{}} (Grave) and `~` |
| `1` | Main typing pad `1` and `!` |
| `2` | Main typing pad `2` and `@` |
| `3` | Main typing pad `3` and `#` |
| `4` | Main typing pad `4` and `$` |
| `5` | Main typing pad `5` and `%` |
| `6` | Main typing pad `6` and `^` |
| `7` | Main typing pad `7` and `&` |
| `8` | Main typing pad `8` and `*` |
| `9` | Main typing pad `9` and `(` |
| `0` | Main typing pad `0` and `)` |
| `Q` | `q` and `Q` |
| `W` | `w` and `W` |
| `E` | `e` and `E` |
| `R` | `r` and `R` |
| `T` | `t` and `T` |
| `Y` | `y` and `Y` |
| `U` | `u` and `U` |
| `I` | `u` and `I` |
| `O` | `o` and `O` |
| `P` | `p` and `P` |
| `A` | `a` and `A` |
| `S` | `s` and `S` |
| `D` | `d` and `D` |
| `F` | `f` and `F` |
| `G` | `g` and `G` |
| `H` | `h` and `H` |
| `J` | `j` and `J` |
| `K` | `k` and `K` |
| `L` | `l` and `L` |
| `Z` | `z` and `Z` |
| `X` | `x` and `X` |
| `C` | `c` and `C` |
| `V` | `v` and `V` |
| `B` | `b` and `B` |
| `N` | `n` and `N` |
| `M` | `m` and `M` |
| `MINS` | `-` (Minus) and `_` |
| `EQL` | `=` (Equal) and `+` |
| `LBRC` | `[` (Left Bracket) and `{` |
| `RBRC` | `]` (Right Bracket) and `}` |
| `SCLN` | `;` (Semicolon) and `:` |
| `QUOT` | `'` and `"` (Single and Double Quote) |
| `NUHS` | Non-US `#` (Hash) and `~` |
| `NUBS` | Non-US `\` (Backslash) and `|` |
| `COMM` | `,` (Comma) and `<` |
| `DOT` | `.` (Dot) and `>` |
| `SLSH` | `/` (Slash) and `?` |
| `TAB` | Tab (Horizontal Tabulation) |
| `CAPS` | Caps Lock |
| `BSPC` | Backspace or Backward Delete |
| `ENT` | Main typing pad Enter or Return |
| `LSFT` | Left Shift |
| `RSFT` | Right Shift |
| `LCTL` | Left Control |
| `RCTL` | Right Control |
| `LOPTN` | (Left) Option (Mac only, special custom action key), same keycode as Windows Left Alt |
| `ROPTN` | (Right) Option (Mac only, special custom action key), same keycode as Windows Right Alt (AltGr) |
| `LCMMD` | (Left) Command (Mac only, special custom action key), same keycode as Windows Left OS |
| `RCMMD` | (Right) Command (Mac only, special custom action key), same keycode as Windows Right OS |
| `LWIN` | Left OS (Windows only), same keycode as Mac (Left) Command |
| `RWIN` | Right OS (Windows only), same keycode as Mac (Right) Command |
| `LALT` | Left Alt (Windows only), same keycode as Mac (Left) Option |
| `RALT` | Right Alt/AltGr (Windows only), same keycode as Mac (Right) Option |
| `TT(N)` | Momentarily turn on layer `N` when pressed and toggles layer `N` on/off permanently if quickly tapped 2 times (this requires `____` on the same key in destination layer) |
| `INS` | Insert |
| `DEL` | Delete or Forward Delete |
| `HOME` | Home |
| `END` | End |
| `PGUP` | Page Up |
| `PGDN` | Page Down |
| `UP` | Up Arrow |
| `DOWN` | Down Arrow |
| `LEFT` | Left Arrow |
| `RGHT` | Right Arrow |
| `NUM` | Keypad Num Lock and Clear |
| `PSLS` | Keypad `/` (Slash) |
| `PAST` | Keypad `*` (Asterisk) |
| `PMNS` | Keypad `-` (Minus) |
| `P1` | Keypad `1` and End |
| `P2` | Keypad `2` and Down Arrow |
| `P3` | Keypad `3` and Page Down |
| `P4` | Keypad `4` and Left Arrow |
| `P5` | Keypad `5` |
| `P6` | Keypad `6` and Right Arrow |
| `P7` | Keypad `7` and Home |
| `P8` | Keypad `8` and Up Arrow |
| `P9` | Keypad `9` and Page Up |
| `P0` | Keypad `0` and Insert |
| `PDOT` | Keypad `.` (Dot) and Delete |
| `PPLS` | Keypad `+` |
| `PENT` | Keypad Enter or Return |

### Media and function keys (top row)

| Keycode label | Description |
| ---- | ---------------- |
| `BRID` | Media: screen brightness down |
| `BRIU` | Media: screen brightness up |
| `MCTL` | Media: open mission control (Mac only) |
| `LPAD` | Media: open launchpad (Mac only) |
| `TASK` | Media: open task view (Windows only, special custom action key) |
| `FLXP` | Media: open file explorer (Windows only, special custom action key) |
| `RGB VAD` | RGB lighting: decrease value (brightness), increase value when Shift is held |
| `RGB VAI` | RGB lighting: increase value (brightness), decrease value when Shift is held |
| `MPRV` | Media: previous track |
| `MPLY` | Media: play/pause track |
| `MNXT` | Media: next track |
| `MUTE` | Media: toggle sound mute |
| `VOLD` | Media: volume down (on Mac: finer control when holding Shift + Option) |
| `VOLU` | Media: volume up (on Mac: finer control when holding Shift + Option) |
| `SNAP` | Media: screenshot or snapshot (Mac only, special custom action key) |
| `SIRI` | Media: use Siri (Mac only, special custom action key) |
| `PSCR` | Print Screen/System Request (Windows only) |
| `SCRL` | Scroll Lock (Windows only) |
| `PAUS` | Pause/Break (Windows only) |
| `RGB MOD` | RGB lighting: cycle forward through modes, reverse direction when Shift is held |
| `RGB TOG` | RGB lighting: Toggle RGB lighting on or off |
| `EJCT` | Media: eject (Mac only) |
| `PWR` | Media: system power down (Mac only, must be held for 3 seconds and a prompt will be displayed) |
| `SLEP` | Media: system sleep (Mac only, must be held for 3 seconds and a prompt will be displayed) |
| `WAKE` | Media: system wake (Mac only, must be held for 3 seconds and a prompt will be displayed) |
| `WSCH` | Media: browser search or www search (Windows only) |
| `MAIL` | Media: launch mail (Windows only) |
| `CALC` | Media: launch calculator (Windows only) |
| `MSEL` | Media: select, launch Media Player (Windows only) |
| `F1` ... `F16` | Function keys: F1 to F16 |

### FN layers keys

| Keycode label | Description |
| ---- | ---------------- |
| `____` or `TRNS` | Transparent keys: use the next lowest non-transparent key on lower layers |
| `RGB TOG` | RGB lighting: Toggle RGB lighting on or off |
| `RGB MOD` | RGB lighting: cycle forward through modes, reverse direction when Shift is held |
| `RGB RMOD` | RGB lighting: cycle through modes in reverse, forward direction when Shift is held |
| `RGB VAI` | RGB lighting: increase value (brightness), decrease value when Shift is held |
| `RGB VAD` | RGB lighting: decrease value (brightness), increase value when Shift is held |
| `RGB HUI` | RGB lighting: increase hue, decrease hue when Shift is held |
| `RGB HUD` | RGB lighting: decrease hue, increase hue when Shift is held |
| `RGB SAI` | RGB lighting: increase saturation, decrease saturation when Shift is held |
| `RGB SAD` | RGB lighting: decrease saturation, increase saturation when Shift is held |
| `RGB SPI` | RGB lighting: increase effect speed, decrease speed when Shift is held |
| `RGB SPD` | RGB lighting: decrease effect speed, increase speed when Shift is held |
| `DB TOGG` | Toggle debug mode on or off |
| `NK TOGG` | Toggle N-key rollover on or off |
| `QK RBT` | Reboot the keyboard, like unplugging and plugging in the USB cable (by itself, it does not load the bootloader to enter into DFU mode for flashing) |
| `EE CLR` | Clears the keyboard's EEPROM (persistent memory) |
| `WH U` | Mouse: Wheel Up |
| `WH D` | Mouse: Wheel Down |
| `WH L` | Mouse: Wheel Left |
| `WH R` | Mouse: Wheel Right |
| `BTN1` | Mouse: Button 1, Left Click |
| `BTN2` | Mouse: Button 2, Right Click |
| `BTN3` | Mouse: Button 3, Middle Button |
| `BTN4` | Mouse: Button 4, Backward Button |
| `BTN5` | Mouse: Button 5, Forward Button |
| `BTN6` | Mouse: Button 6 |
| `BTN7` | Mouse: Button 7 |
| `BTN8` | Mouse: Button 8 |
| `MS U` | Mouse: Cursor Up |
| `MS D` | Mouse: Cursor Down |
| `MS L` | Mouse: Cursor Left |
| `MS R` | Mouse: Cursor Right |

### USB HID keyboard scan codes

The keyboard (referred to as the device) communicates with the host computer operating system via USB. Each time a key is pressed, the keyboard firmware ultimately sends USB scan codes to the OS. Those scan codes are specified by the [USB human interface device class](https://www.usb.org/hid) (USB HID class) which is a part of the USB specification for computer peripherals such as keyboards, mice and game controllers.

HID scan codes are defined by 2 numbers: the **usage page** and the **usage ID** (within the page). The large set of HID scan codes available with QMK firmware is, for the most part, recognized by all OS and includes usage IDs from the following usage pages:

* **HID Keyboard/Keypad Usage Page (0x07)** for most of the key scan codes
* **HID Generic Desktop Page (0x01)** for the power down, sleep, and wake scan codes (recognized by Mac OS)
* **HID Button Page (0x09)** for the mouse buttons
* **HID Consumer Page (0x0C)** for various media controls (such as toggling sound mute and much more)

See the following references for the comprehensive set of specified HID scan codes:

* [USB HID Usage Tables, Version 1.12](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf)
* [HID Usage Tables for USB, Version 1.5](https://www.usb.org/sites/default/files/hut1_5.pdf)

Some QMK custom key actions may be actually realized by quickly registering several keystroke to the OS (composite actions). For example, on Windows, registering the scan codes for `Left OS` and `L` will bring the lock screen because it effectively reproduces the key combination `Left OS` + `L` recognized by the OS (despite that no single usage ID exists for the lock screen action).

For completeness and in order to avoid any ambiguity, the HID usage page and usage ID are displayed on the next pages in the form of a small top banner for each key where it makes sense. Keys without HID scan code banner are, mostly, keys associated with internal keyboard actions where no signal is sent to the OS (such at the RGB LED controls or pressing the `Fn` key itself). Notable exceptions are some mouse controls and keys with composite actions.

\newpage

### QMK keymap layer 0: Mac base

![q6-iso_110-qmk_keymap-layer_0-mac_base](qmk_keymap/q6-iso_110-qmk_keymap-layer_0-mac_base.pdf "q6-iso_110-qmk_keymap-layer_0-mac_base")

### QMK keymap layer 1: Mac FN

![q6-iso_110-qmk_keymap-layer_1-mac_fn](qmk_keymap/q6-iso_110-qmk_keymap-layer_1-mac_fn.pdf "q6-iso_110-qmk_keymap-layer_1-mac_fn")

\newpage

### QMK keymap layer 2: Win base

![q6-iso_110-qmk_keymap-layer_2-win_base](qmk_keymap/q6-iso_110-qmk_keymap-layer_2-win_base.pdf "q6-iso_110-qmk_keymap-layer_2-win_base")

### QMK keymap layer 3: Win FN

![q6-iso_110-qmk_keymap-layer_3-win_fn](qmk_keymap/q6-iso_110-qmk_keymap-layer_3-win_fn.pdf "q6-iso_110-qmk_keymap-layer_3-win_fn")

\newpage

## US keycaps layout applied to keymaps (reference)

Keyboards are meant to support a wide range of layouts independently of the keycaps set you are using. Indeed, this support is not actually achieved within the keyboard itself. Instead, the keyboard sends [numerical codes](#usb-hid-keyboard-scan-codes) via USB, which the operating system then interprets and maps to the appropriate characters depending on the user's configured keyboard layout on the OS side. By default, the reference layout is the US layout (even on ISO keyboards). For example, when a Swiss keycaps layout is used and the key with the `Z` character printed on it is pressed, the keyboard actually sends the HID keycode for `Y` (usage page 0x07, usage ID 0x1C) to the OS. If the OS is then configured for use with a Swiss keyboard layout, the correct intended `Z` character is nevertheless retrieved.

The reference US&nbsp;\twemoji{us} layout shown in the next pages is also what will be visible in the VIA configurator, independently of your keycap layout. As the VIA configurator display, the character $\nabla$ is used to indicate the [transparent keys](#fn-layers-keys).

Note that the [Keychron Q6 ISO collection](https://www.keychron.com/products/keychron-q6-qmk-custom-mechanical-keyboard-iso-layout-collection) comes with fully assembled keyboards with UK&nbsp;\twemoji{uk}, German&nbsp;\twemoji{de} (DE), Nordic (Denmark&nbsp;\twemoji{denmark}, Finland&nbsp;\twemoji{finland}, Norway&nbsp;\twemoji{norway}, Sweden&nbsp;\twemoji{sweden}), French&nbsp;\twemoji{fr} (FR), Spanish&nbsp;\twemoji{es} (ES) and Swiss&nbsp;\twemoji{switzerland} (CH) layouts. Additionally, the **Barebone ISO** option is suitable for all ISO countries (e.g.: Italy&nbsp;\twemoji{it}, Portugal&nbsp;\twemoji{portugal}, Hungary&nbsp;\twemoji{hungary}, etc.). With this option, one can build its own keyboard with keycaps in its preferred languages and switches. The firmware proposed here will fit all those layouts without additional requirements, you just need to select the corresponding language on your OS.

\newpage

### US layout layer 0: Mac base

![q6-iso_110-us_layout-layer_0-mac_base](us_ch_layout/q6-iso_110-us_layout-layer_0-mac_base.pdf "q6-iso_110-us_layout-layer_0-mac_base")

### US layout layer 1: Mac FN

![q6-iso_110-us_ch_layout-layer_1-mac_fn](us_ch_layout/q6-iso_110-us_ch_layout-layer_1-mac_fn.pdf "q6-iso_110-us_ch_layout-layer_1-mac_fn")

\newpage

### US layout layer 2: Win base

![q6-iso_110-us_layout-layer_2-win_base](us_ch_layout/q6-iso_110-us_layout-layer_2-win_base.pdf "q6-iso_110-us_layout-layer_2-win_base")

### US layout layer 3: Win FN

![q6-iso_110-us_ch_layout-layer_3-win_fn](us_ch_layout/q6-iso_110-us_ch_layout-layer_3-win_fn.pdf "q6-iso_110-us_ch_layout-layer_3-win_fn")

\newpage

## CH keycaps layout applied to keymaps

As an example of available national layout, the Swiss&nbsp;\twemoji{switzerland} (CH) variant is shown in the next pages. It is based on the **QWERTZ** layout and was designed as a versatile trade-off allowing easy access to frequently used accents of the French, German, and Italian languages. There is a Swiss German and a Swiss French sub-variants between which the only difference is that the German variety has the German umlauts (ü, ö, ä) accessible in the unshifted state, while the French version has the French accented characters (è, é, à) accessible in the unshifted state. The difference is only in the computer OS layout settings (the physical keycaps remain unchanged).

Contrary to some others national layouts, the Swiss keyboard uses English labels and abbreviations for its keys as a kind of neutral solution to avoid favoring or excluding any of the national languages of Switzerland.

\newpage

### CH layout layer 0: Mac base

![q6-iso_110-ch_layout-layer_0-mac_base](us_ch_layout/q6-iso_110-ch_layout-layer_0-mac_base.pdf "q6-iso_110-ch_layout-layer_0-mac_base")

### CH layout layer 1: Mac FN

![q6-iso_110-us_ch_layout-layer_1-mac_fn](us_ch_layout/q6-iso_110-us_ch_layout-layer_1-mac_fn.pdf "q6-iso_110-us_ch_layout-layer_1-mac_fn")

\newpage

### CH layout layer 2: Win base

![q6-iso_110-ch_layout-layer_2-win_base](us_ch_layout/q6-iso_110-ch_layout-layer_2-win_base.pdf "q6-iso_110-ch_layout-layer_2-win_base")

### CH layout layer 3: Win FN

![q6-iso_110-us_ch_layout-layer_3-win_fn](us_ch_layout/q6-iso_110-us_ch_layout-layer_3-win_fn.pdf "q6-iso_110-us_ch_layout-layer_3-win_fn")

\newpage

## Keys matrix

![q6-iso_110-key_matrix](matrix_led_flag/q6-iso_110-key_matrix.pdf "q6-iso_110-key_matrix")

## LEDs indexes

![q6-iso_110-led_index](matrix_led_flag/q6-iso_110-led_index.pdf "q6-iso_110-led_index")

\newpage

## LEDs flags

![q6-iso_110-flag](matrix_led_flag/q6-iso_110-flag.pdf "q6-iso_110-flag")

**LED 8-bits flags legend**

Refer to the QMK RGB matrix [flags description](https://docs.qmk.fm/features/rgb_matrix#flags):

| Bit | Value | Define | Description |
| -- | --- | ------------ | ---------------- |
| 0 | \textttcolor{flag_red}{ \ 1} | \textttcolor{flag_red}{LED\_FLAG\_MODIFIER } | LED for modifier keys |
| 1 | \texttt{ \ 2} | `LED_FLAG_UNDERGLOW` | LED for underglow |
| 2 | \textttcolor{flag_green}{ \ 4} | \textttcolor{flag_green}{LED\_FLAG\_KEYLIGHT } | LED for key backlight |
| 3 | \textttcolor{flag_blue}{ \ 8} | \textttcolor{flag_blue}{LED\_FLAG\_INDICATOR} | Host or keyboard state indicator |
| 4 | \texttt{ 16} | *N/A* | Bit not used, reserved |
| 5 | \texttt{ 32} | *N/A* | Bit not used, reserved |
| 6 | \texttt{ 64} | *N/A* | Bit not used, reserved |
| 7 | \texttt{128} | *N/A* | Bit not used, reserved |

In our case, the following LED flags combinations are defined:

| Bit selection | Value | Usage |
| --- | -- | ------- |
| \textttcolor{flag_red}{0b0001} | \textttcolor{flag_red}{ 1} | \textttcolor{flag_red}{Modifier} |
| \textttcolor{flag_magenta}{0b1001} | \textttcolor{flag_magenta}{ 9} | \textttcolor{flag_red}{Modifier} + \textttcolor{flag_blue}{Indicator} |
| \textttcolor{flag_green}{0b0100} | \textttcolor{flag_green}{ 4} | \textttcolor{flag_green}{Backlight} |
| \textttcolor{flag_cyan}{0b1100} | \textttcolor{flag_cyan}{12} | \textttcolor{flag_green}{Backlight} + \textttcolor{flag_blue}{Indicator} |

\newpage

# VIA configuration

VIA is a configurator (running on your computer OS) that allows users to intuitively remap any key on the keyboard and create numerous macro commands, shortcuts, or key combinations without the need of reflashing the keyboard firmware. If your keyboard supports multiple layers for different operating systems, such as Windows and Mac, users can even customize different settings on each layer. This comes with onboard memory to save your keyboard settings so you don't need to set up everything again when connecting your keyboard to other computers.

The VIA configurator works by communicating with the firmware that is running on the keyboard and by sending commands via USB HID. This provides the ability to modify the default keymaps of the firmware, to adjust other settings and to store all those changes on your keyboard by using a graphical interface on your computer.

The VIA configurator can be accessed as an [online tool](https://www.caniusevia.com/). However, this requires the [WebHID API](https://caniuse.com/?search=webhid) which is only currently supported by Chrome, Edge, and Opera (there is notably no support on Firefox, which has security concerns about it). Fortunately, the VIA configurator is also available as a tools that runs locally on your computer. The installer can be found on [GitHub](https://github.com/the-via/releases/releases). In all cases, the VIA application is identical whether you use the online or the local version. Using the local version is probably more secure but the online version offers more flexibility if you want the ability to configure the keyboard from several computers.

## Connecting the keyboard for the first time

As this keyboard firmware is custom, the necessary keyboard definition is not packed within the VIA application (contrary to the official **Keychron Q6 Knob Version** with **ISO layout** firmware). As a result, when we connect the keyboard for the first time, we will need to provide a definition of the firmware to the VIA application in the form of a **json** file referred to as the **VIA definition**.

1. Open the [online VIA application](https://usevia.app/) with Chrome or launch the locally installed VIA application.

2. Press on the **Authorize device** button and a pop-up will appear. Then, select the **Keychron Q6 Custom** keyboard and press on **Connect**.

3. So far, VIA automatically loads the definition of the official Keychron firmware (which is not suitable for this custom keyboard). Indeed, if you press on the keyboard icon at the top to access the configure tab, the keyboard is presented as the **KEYCHRON Q6 ISO KNOB** on the top right banner: this is the sign that we are using the unsuitable official definition.

4. Therefore, download the custom VIA definition<br>
**keychron_q6_custom_iso_encoder_via_definition.json** from [GitHub: FabienFellay](https://github.com/FabienFellay/qmk_firmware/releases).

5. In VIA, press on the gear icon at the top to access the settings tab and ensure that the **Show Design Tab** option is enabled. Then, press on the brush icon that should now be available at the top to access the design tab. In the design tab, press on the **Load Draft Definition** button, select the previously downloaded **.json** definition and click on the **Open** button.

6. At that moment, you may have to repeat step 2 and, after that, your keyboard is now correctly paired with VIA. Indeed, if you press on the keyboard icon at the top to access the configure tab, the keyboard should be presented as the **KEYCHRON Q6 CUSTOM ISO KNOB** on the top right banner: this is the sign that everything is now set up correctly.

Finally, if you have flashed again the factory firmware and you want to retrieve a suitable official VIA definition for it, open VIA, go to the design tab and remove the current custom VIA definition by pressing on the cross located to the right of the **Draft Definitions** line. Now, VIA will automatically load the definition of the official Keychron firmware. Alternatively, it is also possible to download the officially provided firmware and VIA definition from the [Keychron website](https://www.keychron.com/pages/firmware-and-json-files-of-the-keychron-qmk-keyboards). However, Keychron has now replaced the used of VIA by their own solution called [Launcher](https://www.keychron.com/blogs/news/how-to-use-launcher-to-program-your-keyboard). If you want to remain with the factory firmware, follow [their instructions](https://www.keychron.com/pages/how-to-factory-reset-or-use-the-launcher-web-app-to-flash-firmware-for-your-keyboard) to use their official Launcher solution instead of VIA.

\newpage

## Configuring the keyboard by using VIA

In the settings tab, you can select the keycap theme. It is recommended to use the **CARBON BLACK A** or the **CARBON BLACK B** theme (which closely corresponds to the real color layout of many Keychron Q6 keyboards). In the configure tab, you can reassign every single key of every layer as you wish and define macros: the configuration is stored in the keyboard EEPROM memory. It will notably persist after keyboard reboots and will work on every computers plugged to the keyboard without any additional requirements.

The configure tab also allows to manipulate the RGB lighting settings graphically (press the light bulb icon on the left). However, it is recommended to enable the RGB lighting effects by pressing on `Fn` + `Tab` before a VIA connection if you intend to use the lighting GUI. Indeed, there is no VIA button to toggle it on and it seems that VIA does not refresh its state according to direct lighting control commands send from the keyboard keys, which might be confusing.

\newpage

# Debug mode

Your keyboard can output debug information via a HID console. By default the output is very limited, but you can turn on debug mode to increase the amount of debug output. You can toggle debug mode on or off by pressing on `Fn` + `B`. You can know if the debug mode is enabled by looking at the `B` key which is lighted up in bright white when the debug mode is enabled and the secondary layer is active (i.e. when the `Fn` key is pressed). Even when the debug mode is active, it has been decided to keep the HID console output not very verbose by design: it will mainly provide information about the RGB matrix lighting state.

## Accessing the HID console output

The following tools are available to access the HID console:

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases)
* [QMK CLI](https://docs.qmk.fm/newbs_getting_started#set-up-your-environment)
* [HID Listen](https://www.pjrc.com/teensy/hid_listen.html) (not part of the QMK ecosystem)

The preferred way to access the HID console is to use **QMK Toolbox** (download it from [GitHub: QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) before installing it). Once opened, **QMK Toolbox** automatically connects to the HID console of your keyboard and it should display `HID console connected: Keychron Keychron Q6 Custom ...` in blue.

Pressing on `Fn` + `B` will then display `DEBUG: enabled.` immediately followed by the currently used **keyboard protocol** which can be either `0` (boot protocol) or `1` (non-boot protocol, for normal operations). The keyboard protocol is determined automatically when the keyboard is powered on. Switching to boot protocol allows the keyboard to work even in the presence of BIOS with limited capabilities. This particular mode is restricted to 6KRO which implies that NKRO will not be available even if it is enabled. If your keyboard appears to be stuck in boot protocol while it should not (i.e. when it is connected to a high-level OS), you can make it switch to non-boot protocol by pressing `Fn` + `Backspace` together during 4 seconds (keyboard reboot). However, the firmware has been designed in such a way that wrong keyboard protocol should not happen in the first place.

Once the debug mode is enabled, it will essentially display information about the RGB lighting control events: which RGB matrix mode is used, which color (in the HSV space) is selected for the monochromatic effects, etc. When debug is toggled off by using `Fn` + `B` again, the console displays `DEBUG: disabled.` before silencing all outputs.

An alternative way to connect to the HID console is to use [QMK CLI](https://docs.qmk.fm/newbs_getting_started#set-up-your-environment) (the QMK build environment and command line interface). Type `qmk console` in the QMK CLI: this [command](https://docs.qmk.fm/cli_commands#qmk-console) lets you connect to the keyboard HID console to get the debugging messages. Finally, the [HID Listen](https://www.pjrc.com/teensy/hid_listen.html) standalone application can also be used to display debug messages. Prebuilt binaries for Windows, Linux, and MacOS are available.

Refer to the [QMK documentation](https://docs.qmk.fm/faq_debug) to know more about debugging with QMK.

\newpage

# Building the firmware and documentation

## How to build the binary file firmware

Building the firmware requires the QMK build environment. Follow the QMK documentation in order to [install QMK CLI and setup your environment](https://docs.qmk.fm/newbs_getting_started) (available for Windows, MacOS and Linux). After the installation of QMK CLI, one has to clone the fork [GitHub: FabienFellay/QMK Firmware](https://github.com/FabienFellay/qmk_firmware) of the [GitHub: QMK/QMK Firmware](https://github.com/qmk/qmk_firmware) repository using [Git](https://git-scm.com/). On Windows, the QMK CLI installation includes a version of [Git](https://git-scm.com/), which it is assumed the user is familiar with. Setup QMK by running:

> ```bash
>  qmk setup
>  ```

Notably, QMK will detect the local cloned fork of QMK and set the *QMK Home* according to its local path on your computer. Moreover, it will also sync, initialize and update the needed QMK Git submodules. Compared to the official QMK repos, the only change of the fork is that it simply adds a custom Keychron Q6 keyboard in the folder [GitHub: FabienFellay/QMK Firmware, Branch: q6_custom, Tree: qmk_firmware/keyboards/keychron/q6_custom](https://github.com/FabienFellay/qmk_firmware/tree/q6_custom/keyboards/keychron/q6_custom), which is nothing else than a modification of the official Keychron Q6 keyboard found at [GitHub: QMK/QMK Firmware, Branch: master, Tree: qmk_firmware/keyboards/keychron/q6](https://github.com/qmk/qmk_firmware/tree/master/keyboards/keychron/q6).

After QMK setup, and assuming you are in the `qmk_firmware` root folder, one can compile the firmware by using:

> ```bash
> qmk compile -kb keychron/q6_custom/iso_encoder -km keychron
> ```

The compilation takes some time and could be longer depending on the OS and the corresponding QMK toolchain. The compilation creates a `.build` folder located at the QMK root folder containing the compiled executable. At the end of the process, the needed firmware **keychron_q6_custom_iso_encoder_keychron.bin** will be also copied directly at the QMK root folder for easy access. Refer to the [flashing procedure](#flashing-the-firmware) to properly flash the obtained `.bin` firmware on the keyboard. To clean the compilation artifacts from the repository (i.e., the `.build` folder), type:

> ```bash
> qmk clean
> ```

Moreover, to clean the `.build` folder and the copied `.bin` firmware at the root folder, all at once, use:

> ```bash
> make distclean
> ```

\newpage

## How to build this PDF documentation

Building this very PDF documentation itself requires the following additional tools installed on your system:

* A comprehensive and up-to-date LaTeX distribution. On Windows, one can consider [MiKTeX](https://miktex.org) to get a complete TeX/LaTeX system.
* A [Python](https://www.python.org/) distribution with the Python executable available in your environment path.
* The markup format document converter [Pandoc](https://pandoc.org/). The LaTeX and Python distributions will integrates with Pandoc.
* The vector graphics editor [Inkscape](https://inkscape.org). Indeed, as [rsvg-convert](https://wiki.gnome.org/Projects/LibRsvg), another tool that integrates with Pandoc, was giving unsatisfactory results, Inkscape will be used instead. Regardless of the OS, it must be installed in such a way that the Inkscape executable is available in your environment path.
* The [Git](https://git-scm.com/) version control system. On Windows, one can consider [Git for Windows](https://gitforwindows.org/) in order to get a BASH emulation used to run Git and the script for building the documentation. Alternatively, it is also possible to use the version of BASH and [Git](https://git-scm.com/) that comes with the QMK CLI, as explained in the [firmware compilation procedure](#how-to-build-the-binary-file-firmware).

After installing the prerequisites, and assuming you are in the `qmk_firmware` root folder, one can build the documentation by using:

> ```bash
> bash ./keyboards/keychron/q6_custom/doc/generate_doc.sh
> ```

As for the firmware compilation, the building process takes some time and the generated PDF **keychron_q6_custom_iso_encoder_keychron.pdf** will be also copied directly at the QMK root folder for easy access. The script **generate_doc.sh** removes some intermediate PDF files converted from their SVG source after having built the final documentation PDF. To keep those files, one can use the `--no_clean` argument. Moreover, if you are repeatedly building the documentation PDF (for example during its composition), one can avoid the time consuming SVG to PDF conversion by using the `--no_convert` argument (this only makes sense after a first build with the `--no_clean` argument). Then, use repeatedly:

> ```bash
> bash ./keyboards/keychron/q6_custom/doc/generate_doc.sh \
>     --no_convert --no_clean
> ```
