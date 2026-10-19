
RGB_MATRIX_EFFECT(layered_effect)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool(*rgb_effect_layers[])(effect_params_t*) = {
};

static bool layered_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (size_t n = 0; n != sizeof(rgb_effect_layers); ++n) {
        rgb_effect_layers[n](params);
    }
    return rgb_matrix_check_finished_leds(led_max);
}


#endif
