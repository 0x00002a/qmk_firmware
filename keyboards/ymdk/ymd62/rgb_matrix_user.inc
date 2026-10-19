
#ifdef __CLANGD_SHIM__
#define RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#else
RGB_MATRIX_EFFECT(layered_effect)
RGB_MATRIX_EFFECT(multi_colour_wave)
#endif

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool(*rgb_effect_layers[])(effect_params_t*) = {
};


static const HSV colour_wave_series[] = {
    {HSV_CYAN},
    {HSV_PINK},
    {HSV_WHITE},
};

static const int8_t colour_wave_w = 3;


static bool multi_colour_wave(effect_params_t* params) {
    const HSV background = rgb_matrix_config.hsv;
    (void)background;

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t led = led_min; led < led_max; ++led) {
        led_point_t pt = g_led_config.point[led];

        const uint8_t xpos = (pt.x * g_rgb_timer) % (sizeof colour_wave_series * colour_wave_w);
        const HSV hc = colour_wave_series[xpos];
        const RGB rgb = hsv_to_rgb(hc);

        rgb_matrix_set_color(led, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);
}

static bool layered_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (size_t n = 0; n != sizeof(rgb_effect_layers); ++n) {
        rgb_effect_layers[n](params);
    }
    return rgb_matrix_check_finished_leds(led_max);
}


#endif
