
RGB_MATRIX_EFFECT(layered_effect)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
//#include "rgb_matrix_types.h"
//#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static const HSV layer_colours[] = {
    HSV_AZURE,
    HSV_ORANGE,
};

static bool layer_selection_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    if (layer >= sizeof(layer_colours)) {
        layer = 0;
    }
    HSV hsv = layer_colours[layer];

    hsv.v = scale8(abs8(sin8(g_rgb_timer >> 2) - 128) * 2, hsv.v);
    RGB rgb = hsv_to_rgb(hsv);

    // select only the function keys, so not escape or backspace
    for (uint8_t c = 1; c < (MATRIX_COLS - 1); ++c) {
        uint8_t led = g_led_config.matrix_co[0][c];
        if (led == NO_LED || led < led_min || led >= led_max) {
            continue;
        }
        rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);

}

static bool(*rgb_effect_layers[])(effect_params_t*) = {
    layer_selection_effect,
};

static bool layered_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (size_t n = 0; n != sizeof(rgb_effect_layers); ++n) {
        rgb_effect_layers[n](params);
    }
    return rgb_matrix_check_finished_leds(led_max);
}


#endif
