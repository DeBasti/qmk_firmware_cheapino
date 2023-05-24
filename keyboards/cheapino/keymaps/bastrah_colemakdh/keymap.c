// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


// Left-hand home row mods
#define HOME_A LGUI_T(KC_A)
#define HOME_R LALT_T(KC_R)
#define HOME_S LCTL_T(KC_S)
#define HOME_T LSFT_T(KC_T)

// Right-hand home row mods
#define HOME_N RSFT_T(KC_N)
#define HOME_E RCTL_T(KC_E)
#define SON_I  LT(son,KC_I)
#define HOME_O RGUI_T(KC_O)

// Auto Control
#define AC_C LT(10,KC_C) //Unused layer is used as placeholder and replaced by CTRL in "process_record_user" function
#define AC_V LT(10,KC_V)

enum layer_names {
    _base,
    nav,
    sym,
    num,
    son,
    tri
};

//Default is tap preferred behavior, for shift it's hold preferred behavior
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_BSPC):
            // Force the dual-role key press to be handled as a modifier if any
            // other key was pressed while the mod-tap key is held down.
            return true;
        default:
            // Do not force the mod-tap key press to be handled as a modifier
            // if any other key was pressed while the mod-tap key is held down.
            return false;
    }
}

//Used for AutoControl C and V
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {          // Return true for normal processing of tap keycode
        case AC_C:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-C
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case AC_V:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┐
      * │ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │
      * ├───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┤
      * │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │
      * └───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┘
      *           ┌───┐                   ┌───┐
      *           │GUI├───┐           ┌───┤Alt│
      *           └───┤Bsp├───┐   ┌───┤Ent├───┘
      *               └───┤   │   │   ├───┘
      *                   └───┘   └───┘
      */

    [_base] = LAYOUT_split_3x5_3(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Z,    LSFT(KC_NONUS_HASH),
        HOME_A,  HOME_R,  HOME_S,  HOME_T,  KC_G,                               KC_M,    HOME_N,  HOME_E,  SON_I,   HOME_O, 
        KC_Y,    KC_X,    AC_C,    KC_D,    AC_V,                               KC_K,    KC_H,    KC_COMM, KC_DOT,  LSFT(KC_MINUS),
                                   LT(nav,KC_SPC), LT(num,KC_TAB), KC_ESC,      KC_ESC,  LT(sym,KC_ENT),  LSFT_T(KC_BSPC)
    )
    
};