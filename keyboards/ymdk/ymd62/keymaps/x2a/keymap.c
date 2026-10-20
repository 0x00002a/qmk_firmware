// Copyright 2024 Richard Dawe (@richdawe)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include <lib/lib8tion/lib8tion.h>

#include <stdint.h>


void td_layer_up_fn(tap_dance_state_t* state, void* user_data) {
    if (state->count == 1) {
        set_oneshot_layer(1, 1);
    } else if (state->count > 1) {
        layer_state_set_user(layer_state | 1);
    } else {
        return;
    }
    reset_tap_dance(state);
}

enum {
    TD_LAYER_UP,
};
tap_dance_action_t tap_dance_actions[] = {
    [TD_LAYER_UP] = ACTION_TAP_DANCE_FN(td_layer_up_fn),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_60_iso( /* Base */
    QK_GESC,  KC_1,     KC_2,     KC_3,  KC_4,  KC_5,  KC_6,    KC_7,  KC_8,  KC_9,     KC_0,     KC_MINS,  KC_EQL,  KC_BSPC,
    KC_TAB,   KC_Q,     KC_W,     KC_E,  KC_R,  KC_T,  KC_Y,    KC_U,  KC_I,  KC_O,     KC_P,     KC_LBRC,  KC_RBRC,
    KC_CAPS,  KC_A,     KC_S,     KC_D,  KC_F,  KC_G,  KC_H,    KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS, KC_ENT,
    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,  KC_C,  KC_V,  KC_B,    KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,           KC_RSFT,
    KC_LCTL,  KC_LGUI,  KC_LALT,                       KC_SPC,                                     TD(TD_LAYER_UP), KC_LEFT,  KC_UP,  KC_RIGHT),

[1] = LAYOUT_60_iso( /* FN */
    KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL ,
    KC_TRNS,  KC_TRNS,  KC_UP,    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  QK_BOOT  ,
    KC_TRNS,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_TRNS,  RM_TOGG,  RM_NEXT,  RM_PREV,  RM_HUEU,  RM_HUED,  RM_SATU,  RM_SATD,  RM_VALU,  RM_VALD,  RGB_M_P,  KC_TRNS,            KC_TRNS,
    KC_VOLD,  KC_VOLU,  KC_MUTE,                                KC_TRNS,                               TO(0), KC_TRNS,  KC_TRNS,  KC_TRNS)
};

static const HSV layer_colours[] = {
    {HSV_AZURE},
    {HSV_AZURE},
};

void ctrl_layer_key_highlights(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);

    if (layer == 0) return; // don't care about first layer

    if (layer >= sizeof(layer_colours)) {
        layer = 0;
    }
    HSV hsv = layer_colours[layer];
    hsv.v = rgb_matrix_config.hsv.v;

    RGB rgb = hsv_to_rgb(hsv);

    // select only the function keys, so not escape or backspace
    for (uint8_t c = 1; c < (MATRIX_COLS - 1); ++c) {
        uint8_t led = g_led_config.matrix_co[0][c];
        if (led == NO_LED) {
            continue;
        }
        rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
    }

}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // caplock
    uint8_t capslock_led = g_led_config.matrix_co[2][0];
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(capslock_led, RGB_AZURE);
    } else {
        rgb_matrix_set_color(capslock_led, 0, 0, 0);
    }

    ctrl_layer_key_highlights(led_min, led_max);



    return false;

}
