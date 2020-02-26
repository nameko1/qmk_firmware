/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SSD1306OLED

#define USE_SERIAL_PD2

#ifdef TAP_DANCE_ENABLE
  #define TAPPING_FORCE_HOLD
  #define TAPPING_TERM 200
  #define NORMAL TD(ETNTER_NORMAL_MODE)
#endif

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

// Multi Tap
#define MT_SS MT(MOD_LSFT, KC_SPC)
#ifdef COMBO_ENABLE
    #define COMBO_COUNT         2
    #define COMBO_TERM          200
#endif

#ifdef LEADER_ENABLE
    #define LEADER_PER_KEY_TIMING
    // #define LEADER_TIMEOUT 250
    #define LEADER_TIMEOUT 350
#endif

// key tap macros
#define TAP_KEY(k) tap_code16(k);
#define TAP_HOME tap_code16(LGUI(KC_LEFT));
#define TAP_END tap_code16(LGUI(KC_RIGHT));
#define TAP_COPY tap_code16(LGUI(KC_C));
#define TAP_CUT tap_code16(LGUI(KC_X));
